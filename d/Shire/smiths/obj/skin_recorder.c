/*
   ~Shire/smiths/obj/leather_recorder.c

   This item will record objects in order to find skins from everywhere.
   11 Sep 99    Created by Kesor
*/
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/container";

#include "smiths.h"

private string *Skin_list = ({ });

static int disallow_alarm = 0;

void give_back(object ob, object dest);
void give_back_skin(object ob, object dest);
void give_back_other(object ob, object dest);

public void
create_container()
{
   set_name(({"device","recorder","hole"}));
   set_short("red gnomish device");
   set_adj(({"red","gnomish"}));
   add_adj(({"skin","pelt","fur","hide"}));  // For use w/"recorder"

   set_long("A small device colored red with a hole in it. The small label "
   + "at its bottom edge reads \"Gnomish make!\". There are various "
   + "grinds and wheels and springs that spin and twist inside it. "
   + "It stands on a silver pole and the pole is nailed to the floor. "
   + "A small blue label on the pole contains instructions of its use.\n");

   add_item("label", "There are two labels on the device, a small one and "
   + "a blue one. Be more specific.\n");
   add_cmd_item("label", "read", "There are two labels on the device, a small "
   + "one and a blue one. Be more specific.\n");
   add_item(({"hole","square hole"}),
     "It is a square hole in the middle of the device. Its size should "
   + "suffice if you try to put a small object inside.\n");
   add_item("small label", "It's the traditional label of gnomish designed "
   + "and made devices.\n");
   add_cmd_item("small label", "read", "The label reads: \"Gnomish make!\"\n");
   add_item(({"grind", "grinds", "wheel", "wheels", "spring", "springs"}),
     "Inside the device, when looking through the hole you can spot various "
   + "gadgets spinning and twisting in different directions and paths. "
   + "just like in most gnomish devices.\n");
   add_item("spinning gadgets", "The small wheels inside the device "
   + "spin in various directions.\n");
   add_item("twisting gadgets", "The springs inside the device twist and turn"
   + "up, down and to the sides.\n");
   add_item("gadgets", "The grinds, wheels and springs inside the red device "
   + "seem to be alive, they twist and turn and spin and move all around "
   + "the inside making small clicks and knocks.");
   add_item(({"pole", "silver pole", "nailed pole"}),
     "The silver pole is nailed to the floor, and at its top affixed the "
   + "red gnomish device.\n");
   add_item("blue label", "The blue label is affixed to the silver pole "
   + "and on it written the directions about how to use the red device.\n");
   add_cmd_item(({"blue label","directions"}), "read",
     "This device is a gnomish skin recorder. It stands here to record all "
   + "skins, pelts, hides, furs and the likes of it that the members of the "
   + "Smiths Guild find on their travels and give to Bigerin to make leather "
   + "of. The idea is that it will record the skin origin, and at later date "
   + "Bigerin will get a report about all skins found around this world and "
   + "learn them. This way he could improve his services.\n\n"
   + "To use the device, simply put the skin that you want to be recorded "
   + "into the device hole. The skin will be returned to you after record.\n"
   + "Thank you, Bigerin the Smiths Guild Tanner.\n");

   add_prop(OBJ_M_NO_GET,"The device is nailed to the floor.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(CONT_I_MAX_VOLUME, 1000000); /* 100 litres is enough for skins */
   add_prop(CONT_I_MAX_WEIGHT, 1000000); /* 100 Kg */

   restore_object(MASTER);
}

public void
init()
{
    ::init();
}

public void
make_sound()
{
    string str;

    switch (random(4))  {
        case 0: str = "You hear a click coming from the red device.\n";
                break;
        case 1: str = "A knock is coming out of the device that stands "
                + "on the silver pole.\n";
                break;
        case 2: str = "There is a turning and twisting sound inside the "
                + "red device.\n";
                break;
        case 3: str = "";
    }
    if (str)
        tell_room(environment(), str);
}

   /* TODO: Check if the "skin" doesn't have "create_weapon" and such */

void
enter_inv(object ob, object from)
{
    string ob_filename;

    ::enter_inv(ob, from);

    if (strlen(function_exists("create_weapon", ob)) ||
        strlen(function_exists("create_armour", ob)) ||
        strlen(function_exists("create_coins",  ob)) ||
        strlen(function_exists("create_container",ob)) ||
        strlen(function_exists("create_drink",  ob)) ||
        strlen(function_exists("create_potion", ob)) ||
        strlen(function_exists("create_torch",  ob)) ||
      !(member_array("skin", ob->query_names()) ||
        member_array("hide", ob->query_names()) ||
        member_array("fur", ob->query_names()) ||
        member_array("pelt", ob->query_names())))
    {
            set_alarm(1.0,0.0,&give_back_other(ob,from));
            return;
    }

    ob_filename = MASTER_OB(ob);

    if (member_array(ob_filename, Skin_list) == -1)
    {
        Skin_list += ({ ob_filename });
        save_object(MASTER);
    }

    set_alarm(1.0,0.0,&give_back_skin(ob,from));
}

void
give_back(object ob, object dest)
{
    if (ob->move(dest))         // Return it to its owner
    {
        dest->catch_msg("You are unable to carry it. It is dropped.\n");
        ob->move(environment(dest));
        return;
    }
    dest->catch_msg("The "+ob->query_name()+" is returned to you.\n");
}

void
give_back_other(object ob, object dest)
{
    tell_room(environment(), "\nThe red device knocks and clicks and "
    + "makes strange noises. A small red flag rises above the red "
    + "device claiming that whatever is inside it - is not a skin.\n");
    set_alarm(1.0,0.0,&give_back(ob, dest));
}

void
give_back_skin(object ob, object dest)
{
    tell_room(environment(), "\nBeeps and bump sound from the red device "
    + "and a spring jumps out from its side. A big green flag rises "
    + "from it claiming that whatever is inside it - can be a skin.\n");
    set_alarm(1.0,0.0,&give_back(ob, dest));
}

void
disallow_enter(object from)
{
    from->catch_msg("\nYou are unable to put more than one item into "
    + "the device.\n");
    disallow_alarm = 0;
}

/*
 * Function name: prevent_enter
 * Description  : This function will prevent the insertion of another object
 *                when there already is an item in the container.
 * Arguments    : object ob - the item the player tries to insert.
 * Returns      : int 1/0 - disallow/allow the object to enter.
 */
public int
prevent_enter(object ob)
{
    if (!disallow_alarm)
        disallow_alarm = set_alarm(1.0,0.0,&disallow_enter(this_player()));

    /* We take the size of the inventory of this container. Then use !! to
     * make any positive number into 1, while 0 remains 0. Thus, if the size
     * of the inventory is non-zero, it will prevent the insertion.
     */
    return !!sizeof(all_inventory());
}


public void
show_visible_contents(object for_obj)
{
  /* I don't want to see "The device is empty." at the end of long() */
}
