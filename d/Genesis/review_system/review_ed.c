/*
 * review_ed.c
 *
 * Mrpr, 1993. 
 *
 * To be used in conjunction with /cmd/wiz_cmd_normal review commands.
 */

inherit "/std/object.c";

#include <macros.h>
#include <filepath.h>
#include <std.h>

#define CALLED_FROM	"/d/Debug/debugwiz/review_ob"
#define BASE_PATH	"/d/Debug/debugwiz/reviews"
#define PO		previous_object()
#define RW_READ		0
#define RW_WRITE	1

create_object()
{
}

nomask public string
ed_file(string file)
{
    if (function_exists("create_object", PO) != CALLED_FROM)
	return "#Illegal call.\n";

    write("Review edit: " + file + "\n");
    ed(file);
    remove_object();
    return "";
}

