/*
 * sandcastle.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Originally made by Gresolle
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#define OTHERROOM NYREESEDIR + "cadu_s3"

object knight;
int bottle, hole;

void hide();
void hide1();
void create_knight();
void destruct_castle();

void
reset_room()
{
    hole = 0;
    remove_item("hole");

    if (!knight)
        create_knight();
    else
        bottle = 1;
}

string
my_long()
{
    string s;

    s = "You are standing in the middle of a huge sand castle that someone " +
        "has built on the shore.\n";

    if (hole) 
        s += "Someone has dug a hole in the sand.\n";

    return s;
}

void
create_room()
{
    set_short("sand castle");
    set_long("@@my_long");

    INSIDE;

    add_exit(OTHERROOM, "out");
 
    add_item("sand", "It is white, slightly damp and very soft. It looks "+
             "exactly like the sand you used to dig in when you were a "+
             "small child.\n");
    bottle = 0;
    hole = 0;
    create_knight();
}
 
void
create_knight()
{
    tell_room(TO, "A sand knight steps out of the wall.\n");

    knight = clone_object(ROKEDIR + "npc/sandknight");
    knight->move(TO);
    set_alarm(3.0, 0.0, hide1);
}

void
hide1()
{
    tell_room(TO, "The sand knight hides something in the ground.\n");
    bottle = 1;
    set_alarm(60.0, 0.0, hide);
}

void
hide()
{
    if (!knight) return;
    tell_room(TO, "The knight stomps on the ground, as if he has hidden " +
              "something.\n");
    set_alarm(60.0, 0.0, hide);
}

void
destruct_castle()
{
    object *objs;
    int t;

    tell_room(TO, "The tide flows in, ruining the former mighty castle.\n");

    if (knight)
    {
        tell_room(TO, "The sand knight is swallowed by the waves.\n");
    }

    objs = all_inventory(TO);

    if (objs && sizeof(objs) != 0)
    {
        for (t = 0; t < sizeof(objs); t++)
        {
            if (interactive(objs[t]))
            {
                if (knight)
                {
                    objs[t]->stop_fight(knight);
                    knight->stop_fight(objs[t]);
                }
                objs[t]->catch_msg("You find yourself out on the shore again.\n");
                tell_room(OTHERROOM, QCNAME(objs[t])+
                          " appears from the ruined castle.\n");
                objs[t]->move(OTHERROOM);
            }
            else
            {
                objs[t]->remove_object();
            }
        }
    }
    bottle = 0;
    hole = 0;
    remove_item("hole");
    remove_object();
}

int
dig()
{
    if (knight)
    {
        TP->catch_msg("The sand knight stops you!\n");
        return 1;
    }

    say(QCTNAME(TP) + " digs in the sand.\n");
    add_item("hole", "The hole goes deep into the sand below you.\n");
    if (!bottle)
    {
        TP->catch_msg("You dig in the sand with your bare hands but find nothing.\n");
        return 1;
    }
    else
    {
        TP->catch_msg("As you dig in the sand you find an old bottle.\n" +
                      "You quickly pick it up and put it in your pocket.\n");
        clone_object(ROKEDIR + "obj/questparcel")->move(TP);
        bottle = 0;
        hole = 1;
        return 1;
    }
}
  
void
init()
{
    ::init();
    
    add_action(dig, "dig");
    add_action(dig, "search");
}
