#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * struct song_s - structure for a song node
 * @name: title of the song
 * @length: length of the song
 * @next: pointer to next song in the playlist
 */
typedef struct song_s
{
    char *name;
    char *length;
    struct song_s *next;
} song_t;

/**
 * struct playlist - playlist of songs
 * @nb_songs: number of songs in playlist
 * @first:  pointer to first song in playist
 */
typedef struct playlist_s
{
    size_t nb_songs;
    song_t *first;
    song_t *last;
} playlist_t;

playlist_t *create_playlist(void);
song_t *create_song(char *name, char *length);
int add_song(playlist_t *playlist, char *name, char *length);
int min_to_sec(char *song_length);
void play_song(song_t *song);
void play_playlist(playlist_t *playlist);

#endif