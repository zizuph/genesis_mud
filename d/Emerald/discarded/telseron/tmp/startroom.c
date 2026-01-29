inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
string *players;
 
void
create_room()
{
    set_short("Township start room");
    set_long( "This is a rather strange room. You should not "+
      "be here, and since you are, something must be wrong with "+
      "the house in which you normally start.\n" );
 
    add_prop(ROOM_I_INSIDE, 1);
 
    seteuid(getuid());
    restore_object(PRIVATE_DIR + "houses");
    if (!players)
    players = ({ });
}
 
void
add_house(object player, string house)
{
    if (member_array(player->query_real_name(), players)>=0)
    return;
    players += ({ player->query_real_name() });
    save_object(PRIVATE_DIR + "houses");
}
 
void
remove_house(object player)
{
    if (member_array(player->query_real_name(), players) < 0)
    return;
    players -= ({ player->query_real_name() });
    save_object(PRIVATE_DIR + "houses");
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob) && !from) {
    if (member_array(ob->query_real_name(), players) < 0)
        return;
    ob->move(TOWNSHIP_DIR + ob->query_real_name());
    }
}
