#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "playlist.h"

int main(void)
{
    playlist_t *playlist = create_playlist();
    if (!playlist)
    {
        printf("Could not create a playlist.\n");
        return 1;
    }

    char choice, song_name[100], song_length[10];
    while (1)
    {
        printf("Menu:\n 1. Add a song to the playlist\n 2. Play the playlist\n");
        printf("3. Exit\n Enter your choice: ");
        scanf("%c", &choice);

        switch (choice)
        {
        case '1':
            printf("Enter the name of the song: ");
            scanf(" %[^\n]s", song_name);
            printf("Enter the length of the song (format minutes:seconds): ");
            scanf("%s", song_length);
            if (add_song(playlist, song_name, song_length))
                printf("Song added to playlist!\n");
            else
                printf("Error: could not add the song.\n");
            break;

        case '2':
            if (playlist->nb_songs == 0)
                printf("The playlist empty. Add songs first.\n");
            else
                play_playlist(playlist);
            break;
        
        case '3':
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}