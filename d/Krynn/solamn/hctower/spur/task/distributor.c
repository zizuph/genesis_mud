/* This object is able to pick an object from a list, clone it and
 * move it to someplace in Krynn.
 *
 * The save file holds these infos:
 *  array of rooms where it can be put. (along with a standard id for each of those)
 *  array of object descriptions.
 *
 * the command would be something like:
 * 'order squire to place <thing> at <place>'
 * short: 'place <thing> at <place>'
 * placing can only be done from special rooms.
 *
 * additional commands would be 'new item <thing> <short>'
 * with an editor for the long description.
 *
 * 'new place here' will add the current room to the
 * list of rooms.
 *
 * 'remove place here'
 * 'remove item <thing>'
 */

inherit "/std/object";

void
create_object()
{
    set_short("distributor");
    set_long("");
}

void
init()
{
    ADA("kcnew");
    ADA("kcplace");
    ADA("kcorder");
}

int
kcnew(string str)
{
    
    return 1;
}

int
kcplace(string str)
{

}

int
kcorder(string str)
{
    int res;
    
    NF("KcOrder what?\n");
    if (!str)
      return 0;
    if (sscanf(str,"squire to %s",str) != 1)
      return 0;
    res = place(str);
    return res;
}
