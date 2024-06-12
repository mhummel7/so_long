/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhummel <mhummel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 08:26:33 by mhummel           #+#    #+#             */
/*   Updated: 2024/06/12 10:42:19 by mhummel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

#define MAP_WIDTH 8
#define MAP_HEIGHT 7
#define TILE_SIZE 64

typedef struct {
    char symbol; // Das Symbol des Elements
    char *png_file; // Der Dateiname der PNG-Datei
} MapElement;

typedef struct {
    int x; // x-Position des Spielers
    int y; // y-Position des Spielers
} Player;

char map_data[MAP_HEIGHT][MAP_WIDTH]; // Hier speicherst du die Karteninformationen
int total_collectibles = 0; // Variable zur Speicherung der Gesamtanzahl der Sammelobjekte
int collected_collectibles = 0; // Variable zur Speicherung der Anzahl der gesammelten Sammelobjekte
int key_count; // Variable zur Speicherung der Anzahl der Tastenanschläge

MapElement elements[] = {
    {'1', "src/textures/wall.png"},  // Wand
    {'0', "src/textures/floor.png"}, // Boden
    {'E', "src/textures/exit.png"}, // Ausgang
    {'P', "src/textures/player.png"}, // Spieler
    {'C', "src/textures/collectible.png"} // Sammelobjekt
};

Player player; // Die Position des Spielers

void load_map(const char *filename) {
    // Öffnen Sie die .ber-Datei und lesen Sie die Karte ein
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Durchlaufen Sie die Karte und zählen Sie die Sammelobjekte
    int y = 0;
    while (y < MAP_HEIGHT && fscanf(file, "%s", map_data[y]) != EOF) {
        int x = 0;
        while (x < MAP_WIDTH) {
            if (map_data[y][x] == 'C') {
                total_collectibles++; // Inkrementieren Sie die Anzahl der Sammelobjekte
            }
            x++;
        }
        y++;
    }

    fclose(file);

    // Initialisieren Sie die Position des Spielers und setzen Sie den Boden unter ihn
    y = 0;
    while (y < MAP_HEIGHT) {
        int x = 0;
        while (x < MAP_WIDTH) {
            if (map_data[y][x] == 'P') {
                player.x = x;
                player.y = y;
                map_data[y][x] = '0'; // Setze den Boden unter den Spieler
                return;
            }
            x++;
        }
        y++;
    }
}

void draw_tile(mlx_t *mlx, char symbol, int x, int y) {
    int i = 0;
    while (i < (int)(sizeof(elements) / sizeof(elements[0]))) {
        if (elements[i].symbol == symbol) {
            mlx_texture_t* texture = mlx_load_png(elements[i].png_file);
            if (!texture) {
                fprintf(stderr, "Error: Could not load texture %s\n", elements[i].png_file);
                exit(1);
            }
            mlx_image_t* img = mlx_texture_to_image(mlx, texture);
            if (!img) {
                fprintf(stderr, "Error: Could not convert texture to image %s\n", elements[i].png_file);
                mlx_delete_texture(texture);
                exit(1);
            }
            mlx_image_to_window(mlx, img, x * TILE_SIZE, y * TILE_SIZE);
            mlx_delete_texture(texture);
            break;
        }
        i++;
    }
}

void display_map(mlx_t *mlx) {
    int y = 0;
    int x;

    // Finde die Spielerposition und zeichne die Karte, indem du jede Kachel einzeln zeichnest
    while (y < MAP_HEIGHT) {
        x = 0;
        while (x < MAP_WIDTH) {
            draw_tile(mlx, map_data[y][x], x, y);
            x++;
        }
        y++;
    }
}

void update_map_and_display(mlx_t *mlx, int old_x, int old_y) {
    // Überprüfen, ob das Ziel kein Ausgang ist und nicht bereits ein Boden ist
    if (map_data[old_y][old_x] != 'E' && map_data[old_y][old_x] != '0') {
        // Setze die alte Position des Spielers auf Boden (0)
        map_data[old_y][old_x] = '0';
    }

    // Wenn der Ausgang nicht unter dem Spieler ist, setze ihn auf Ausgang zurück
    if (map_data[player.y][player.x] != 'E') {
        map_data[player.y][player.x] = 'P';
    }

    // Prüfe, ob alle Sammelobjekte eingesammelt wurden und der Spieler sich auf dem Ausgang befindet
    if (collected_collectibles == total_collectibles && map_data[player.y][player.x] == 'E') {
        // Alle Sammelobjekte eingesammelt und der Spieler erreicht den Ausgang
        // Beenden Sie das Spiel
        mlx_terminate(mlx);
        exit(0);
    }

    // Zeichne die Karte neu
    display_map(mlx);

    // Zeichne den Spieler neu an der aktuellen Position
    draw_tile(mlx, 'P', player.x, player.y);
}

void key_hook(mlx_key_data_t keydata, void* param) {
	mlx_t* mlx = (mlx_t*)param;
	int new_x = player.x;
	int new_y = player.y;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
		if (keydata.key == MLX_KEY_W)
			{
			new_y -= 1;
			key_count++;
			printf("Key count: %d\n", key_count);
			}
		else if (keydata.key == MLX_KEY_A)
			{
			new_x -= 1;
			key_count++;
			printf("Key count: %d\n", key_count);
			}
		else if (keydata.key == MLX_KEY_S)
			{
			new_y += 1;
			key_count++;
			printf("Key count: %d\n", key_count);
			}
		else if (keydata.key == MLX_KEY_D)
			{
			new_x += 1;
			key_count++;
			printf("Key count: %d\n", key_count);
			}
		else if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(mlx);
	}

 if (new_x >= 0 && new_x < MAP_WIDTH && new_y >= 0 && new_y < MAP_HEIGHT && map_data[new_y][new_x] != '1') {
		int old_x = player.x;
		int old_y = player.y;

		// Wenn der Spieler auf ein Sammelobjekt geht, entferne es von der Karte
		if (map_data[new_y][new_x] == 'C') { // Ändern Sie 'c' zu 'C' entsprechend der MapElement-Deklaration
			collected_collectibles++;
			map_data[new_y][new_x] = '0';
			player.x = new_x;
			player.y = new_y;
		} else {
		// Update the player position
			player.x = new_x;
			player.y = new_y;
		}

		update_map_and_display(mlx, old_x, old_y); // Aktualisiere die Anzeige
	}
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
		return 1;
	}

	const char *map_file = argv[1];

	// Lade die Karte aus der .ber-Datei
	load_map(map_file);

	// Initialisiere das Fenster
	mlx_t* mlx = mlx_init(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "so_long", true);
	if (!mlx) {
		fprintf(stderr, "Error: Could not initialize MLX\n");
		return 1;
	}

	// Zeige die Karte an
	display_map(mlx);
	// Zeige den Spieler an
	draw_tile(mlx, 'P', player.x, player.y);

	// Registriere die Tastatur-Eingabe-Callback-Funktion
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
