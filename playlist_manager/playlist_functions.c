#include "playlist.h"

/**
 * create_playlist - creates a new playlist
 * Return: pointer to created playlist or NULL on error
 */
playlist_t *create_playlist(void)
{
    playlist_t *new_playlist = (playlist_t *)malloc(sizeof(playlist_t));
    if (!new_playlist)
        return NULL;

    new_playlist->nb_songs = 0;
    new_playlist->first = NULL;
    new_playlist->last = NULL;
    return new_playlist;
}

/**
 * create_song - creates new song
 * @name: song name
 * @length: song length
 * Return: created song or NULL on error
 */
song_t *create_song(char *name, char *length)
{
    song_t *new_song;
    if (!name || !length)
        return NULL;

    new_song = (song_t *)malloc(sizeof(song_t));
    if (!new_song)
        return NULL;

    new_song->name = strdup(name);
    new_song->length = strdup(length);
    new_song->next = NULL;

    return new_song;
}

/**
 * add_song - adds song to playlist
 * @playlist: playlist to add song to
 * @name: name of song
 * @length: length of the song
 * Return: 1 on success or 0 on failure
 */
int add_song(playlist_t *playlist, char *name, char *length)
{
    song_t *new_song, *temp;
    if (!playlist || !name || !length)
        return 0;

    new_song = create_song(name, length);
    if (!new_song)
        return 0;
    
    if (playlist->nb_songs == 0)
    {
        playlist->first = new_song;
        playlist->last = new_song;
    }
    else
    {
        playlist->last->next = new_song;
        playlist->last = new_song;
    }
    playlist->nb_songs++;
    return 1;
}

/**
 * min_to_sec - converts song length to seconds
 * @song_length: input song length
 * Return: time in seconds
 */
int min_to_sec(char *song_length)
{
    int min, sec, i;
    if (!song_length)
        return 0;
    min = 0, sec = 0;
    for (i = 0; song_length[i] != ':'; i++)
    {
        min = (min * 10) + (song_length[i] - '0');
    }
    if (song_length[i] == ':')
    {
        i++;
    }
    while (song_length[i] != '\0')
    {
        sec = (sec * 10) + (song_length[i] - '0');
        i++;
    }
    return (min * 60 + sec);
}

/**
 * play_song - plays a single song from start to finish
 * @song: current song
 */
void play_song(song_t *song)
{
    int duration, count;
    if (song)
    {
        count = 0;
        duration = min_to_sec(song->length);
        printf("Playing: %s [length: %s]\n", song->name, song->length);
        while (count <= 20)
        {
            printf("# ");
            usleep((duration * 1000000) / 20);
            count++;
        }
        printf("\n");
    }
}

/**
 * play_playlist - play all songs in playlist
 * @playlist: current playlist
 */
void play_playlist(playlist_t *playlist)
{
    song_t *current_song = playlist->first;
    while (current_song)
    {
        play_song(current_song);
        current_song = current_song->next;
    }
    printf("Playlist finished!\n");
}