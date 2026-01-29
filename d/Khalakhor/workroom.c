/**********************************************************************
 * - workroom.c                                                     - *
 * - New Khalakhor workroom. Created with board that is only        - *
 * - readable by domainmmembers and arches+                         - *
 * - Created by Damaris@Genesis 01/2005                             - *
 * - Minor update Tapakah 07/2021                                   - *
 **********************************************************************/

#pragma strict_types

inherit "/std/workroom";
#include "laying.c"
#include "pit.c"
#include <macros.h>
#include <stdproperties.h>
private string query_no_scry ();
private string query_entity ();

void
create_workroom ()
{
    ::create_workroom();
    add_prop(ROOM_M_NO_SCRY, query_no_scry);
    set_short("a grass filled knoll");
    set_long("   The most vibrant green grass saturates this "+
      "knoll with its beauty and majesty. Along the edge of the "+
      "circumference it has startling flowers of all different shapes, "+
      "sizes and colours. From the top of this knoll the vision of "+
      "Khalakhor can be seen with the splendor of ages being passed "+
      "down from one tale to another all spanned out before ones "+
      "eyes. The center of this knoll has a fire pit that has been "+
      "dug with precision. Every now and again this pit burns with "+
      "flames that fuel the imaginations of wizards making this a "+
      "truly mystical and magical place.\n\n");
    add_item(({"grassy knoll", "area", "room", "workroom", "knoll"}), query_long);
    add_item(({"flowers", "flower"}),
      "There are so many different flowers with different shapes, "+
      "sizes and colours. They encircle the grassy knoll with grace "+
      "and beauty.\n");
    add_item(({"circle"}),
      "There is a circle of cushions that suround the fire pit.\n");
    add_item(({"cushion", "cushions", "grass", "soft grass", "blanket"}), lay_desc);
    add_my_desc(lay_desc, this_object());
    add_exit("/w/tapakah/workroom","tapakah");
    add_exit("/d/Khalakhor/open/project/office", "tower");
    /*
     * Until they come back...
    add_exit("/w/damaris/workroom", "damaris", 0,0,1);
    add_exit("/w/rufus/root_cellar", "rufus",  0,0,1);
    */
}

object
load_board()
{
    object bb;
    string *file;
    string name;

    file = explode(MASTER + "/", "/");
    file = slice_array(file, 0, sizeof(file) - 2);

    seteuid(getuid());
    bb = clone_object("/d/" + creator(this_object()) + "/board");

    name = implode(file, "/") + "/private";
    if (file_size(name) != -2)
        mkdir(name);

    bb->set_board_name(name + "/domain_board");
    bb->set_num_notes(50);
    bb->set_silent(0);
    bb->move(this_object());

    return bb;
}
public void
init ()
{
    ::init();
    init_lay();
    init_fire();

}
private string
query_no_scry ()
{
  string *messages = ({
        " protective blessing prevents this action.",
        " blessing thwarts this action.",
        " protective light neutralizes this action.",
        " defensive blessing prevents this action.",
        " blessed sanction thwarts this action.",
        " shielding light defuses this action.",
        " blessing spoils this attempt.",
        " protective blessing prevents this attempt.",
        " protective light neutralizes this attempt.",
                      });

  return query_entity() + one_of_list(messages);
}

private string
query_entity ()
{
  string *entity = ({
        "Ardagh's",
        "Kinlagh's",
        "Boudin's",
        "An ancient",
                     });

  return entity[random(sizeof(entity))];
}
