/*
 * /d/Gondor/domain/announceboard.c
 *
 * This board is used by the various other boards around the domain to display
 * Middle Earth related announcements. It's special in that it will automatically
 * remove notes that are older as 3 months when the board is cloned.
 *
 * Created by Eowul, Oktober 3rd, 2008
 */

#include <std.h> 
#include <time.h>

// Expiration set to 90 days
#define EXPIRATION_TIME 7776000

inherit "/std/board";

int time_filter(string args)
{
    int file_time = atoi(extract(args, 1));
    int expired_time = time() - file_time;
    if(expired_time > EXPIRATION_TIME) return 1;
    return 0;
}

private void remove_expired_notes(string file)
{
    seteuid(getuid());
	if (file_size(board_name + "_old") == -1)
	    mkdir(board_name + "_old");

	rename(board_name + "/" + file, board_name + "_old/" + file);
}

private void cleanup()
{
    string *notes;

    seteuid(getuid());
    notes = filter(get_dir(board_name + "/b*"), time_filter);
    map(notes, remove_expired_notes);
}

void create_board()
{
    set_board_name("/d/Gondor/private/boards/announceboard");
    set_keep_discarded(1);
    set_num_notes(3);
    cleanup();
}

int block_writer()
{
    string name = this_player()->query_real_name();
    if(SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH) return 0;
    return 1;
}

int allow_remove(int note)
{
    string name = this_player()->query_real_name();
    if(SECURITY->query_wiz_dom(name) == "Gondor" ||
      SECURITY->query_wiz_rank(name) >= WIZ_ARCH) return 1;
    return 0;
}