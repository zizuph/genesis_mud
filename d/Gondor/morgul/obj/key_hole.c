/*
 * /d/Gondor/morgul/obj/key_hole.c
 *
 * a hole in the floor of a cave in Shelob's lair
 *
 * Olorin, Nov 1993
 * Tigerlily, April 22, 2004: Modified for ranger recode
 *     elbereth_scroll updated
 */
#pragma strict_types

inherit "/std/container.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/tunnel/tunnel_door.h"

#define PLAYER_SKILLS ({ TS_DEX, TS_INT })

#ifndef NEW_RANGERS_OPEN
#define SCROLL   "/d/Gondor/common/guild/spells/obj/elbereth_scroll"
#endif

#ifdef NEW_RANGERS_OPEN
#define SCROLL   "/d/Gondor/guilds/rangers/spells/obj/elbereth_scroll"
#endif

int fishing_alarm;
object  key,
        scroll,
        paralyze,
        fisher;

void fishing(object hook);

void create_container()
{
    set_name("hole");
    add_name("drain");
    set_long("@@long_desc");
    set_short("@@short_desc");

    add_prop(OBJ_M_NO_GET,1);
    add_prop(CONT_I_TRANSP,1);
    add_prop(CONT_I_RIGID,1);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_MAX_VOLUME,10000);
    add_prop(CONT_I_MAX_WEIGHT,100000);
    add_prop(CONT_M_NO_REM,"The iron grid prevents you from taking anything out of the hole.\n");

    add_item(({"grid", "metal grid", "rods", "iron rods"}), BSN(
        "In the middle of the cave where the rock floor has been " +
        "cleared from bones, you can see a metal grid covering a hole " +
        "in the ground. The metal grid consists of seven thick iron " +
        "rods that are put into the rock. There is no way to remove them. "));

    set_no_show_composite(1);

    seteuid(getuid());
    reset_container();
    enable_reset();
}

void 
init()
{
    ::init();
    add_action("do_get","get");
    add_action("do_get","fish");
}

void 
add_stuff()
{
    if(!key || !present("key", TO))
    {
        key = clone_object(MORGUL_DIR + "obj/hatch_key2");
        key->move(TO);
    }
    if (!scroll || !present("scroll",TO))
    {
        scroll = clone_object(SCROLL);
        scroll->move(TO);
    }
}

void 
reset_container()
{
    fisher = 0;
    add_stuff();
}

string 
long_desc()
{
    string desc = "This hole covered with the metal grid looks like a drain. " +
        "You wonder who might have put a drain into this forsaken cave. " +
        "Was it meant to take away water or the blood of the many creatures " +
        "that died here? ";

    return BSN(desc);
}

string 
short_desc()
{
    return "hole covered by an iron grid";
}

void 
stop_fishing()
{
    fisher = 0;
    remove_alarm(fishing_alarm);
}

void 
fishing(object hook)
{
    int      task,
             result;

    task = TASK_DIFFICULT;
    if( TP->test_bit("Gondor",MORGUL_GROUP,MORGUL_ENTRY_BIT) )
        task = TASK_FORMIDABLE;
    if( (result = TP->resolve_task(task, PLAYER_SKILLS)) > 0)
    {
        write("You manage to get the key onto the "+hook->query_name()+" and pull it through the grid.\n");
        SAY(" manages to get the key onto the "+hook->query_name()+" and pulls it through the grid.");
        paralyze->remove_object();
        fisher = 0;
        result = key->move(TP,1);
        if(result != 3)
            key->move(ENV(TO));
    /* Set the prop that keeps track if you did your part in the quest */
        TP->add_prop(MORGUL_ENTRY_HATCH,1);

    }
    else
    {
        if (result > -20)
            write(BSN("You get the key onto the "+hook->query_name()+", but when you try to pull " +
                "it through the grid, it slips down again. But you keep trying!"));
        else
            write("You fail to get the key onto the "+hook->query_name()+", but you keep trying.\n");
        SAY(" is fishing with "+LANG_ADDART(hook->query_name())+" in the hole under the grid.");
        fishing_alarm = set_alarm(itof(4 + random(6)), 0.0, &fishing(hook));
    }
}

void 
start_fishing(object hook)
{
    paralyze = clone_object(MORGUL_DIR + "obj/paralyze");
    paralyze->set_stop_message("You stop fishing for the key.\n");
    paralyze->set_stop_object(TO);
    paralyze->set_stop_fun("stop_fishing");
    paralyze->move(TP);

    fisher = TP;
    fishing_alarm = set_alarm(itof(4 + random(6)), 0.0, &fishing(hook));
}

int 
do_get(string str)
{
    string   vb = query_verb();
    mixed    hook;
    int      i,
             ih;

    if(!stringp(str))
    {
        if(vb = "fish")

            NF(CAP(vb) + " for what with what?\n");
        else
            NF(CAP(vb) + " what with what?\n");
        return 0;
    }

    if ( (vb == "get" && parse_command(str, TP, " [iron] [rusty] 'key' 'with' %i ", hook)) 
        || (vb == "fish" && parse_command(str, TP, " [for] [iron] [rusty] 'key' 'with' %i ", hook)) )
    {
        if (!present("key",TO))
        {
            NF("There is no key here!\n");
            return 0;
        }
        ih = 0;
        i = 1;
        while(i < sizeof(hook))
        {
            if (hook[i]->id("hook"))
            {
                ih = i;
                break;
            }
            i++;
        }
        if (ih)
        {
            if(objectp(fisher) && present(fisher,ENV(TO)))
            {
                NF("You cannot do that because " + QTNAME(fisher) + " is blocking the metal grid.\n");
                return 0;
            }
            write("You start to fish for the key with the "+hook[ih]->short()+".\n");
            SAY(" starts to fish for the key under the grid with "+LANG_ADDART(hook[ih]->short())+".");
            start_fishing(hook[ih]);
            return 1;
        }
        NF("You cannot use the "+hook[1]->short()+" to do that!\n");
        return 0;
    }
    else if ((vb == "get" && parse_command(str, TP, " [old] 'scroll' 'from' 'hole' / 'grid' / 'drain' ")))
    {
        if (!present("scroll", TO))
        {
            NF("There is no scroll here!\n");
            return 0;
        }
        if (!IS_RANGER(TP))
        {
            write(BS("You reach your fingers through the grid, and "
              + "manage to grip the end of the old scroll! But you "
              + "sigh disappointedly when your touch seems to make "
              + "it smoulder to pieces.\n"));
            SAY(" slips two fingers through the grid, gripping the "
              + "end of the old scroll, but sighs disappointedly when "
              + "it smoulders to dust.");
            scroll->remove_object();
            return 1;
        }
        else
        {
            write(BS("You reach two fingers through the grid, and "
              + "manage to grip the upper end of the old scroll, "
              + "carefully lifting it out of the hole!\n"));
            SAY(" reaches two fingers through the grid, gripping the "
              + "end of the old scroll, carefully lifting it up out "
              + "of the hole!");
            scroll->move(ENV(TO),1);
            return 1;
        }
    }
    NF("Get what with what?\n");
    return 0;
}
