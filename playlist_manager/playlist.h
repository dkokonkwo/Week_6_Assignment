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

#endif