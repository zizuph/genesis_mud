/*
 * /d/Terel/mountains/ghastly_keep/obj/g_pinecone.c
 *
 *  Just a plain pinecone.
 *
 *  Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

#define hit_locs ({"head", "back", "chest", "right foot",\
                   "left arm", "right arm", "left foot", "torso",\
                   "stomach", "right shoulder", "left shoulder"})

#define hurts ({"weakly", "lightly", "slightly", "accurately",\
                   "powerfully", "forcefully"})

inherit "/cmd/std/command_driver.c";
inherit "/std/object";
#include "../defs.h";

#include <stdproperties.h>
#include <macros.h>

string throw_pinecone(string str);

void
create_object()
{
    set_name("pinecone");
    add_name("_ghastly_keep_pinecone");
    set_adj("brown");
    add_adj(({"brown"}));
    set_short("brown pinecone");

    set_long("This "+short()+ " is covered in ice after a winter storm.\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);

}

public void
init()
{
    ::init();
    add_action(throw_pinecone, "throw");
    add_action(throw_pinecone, "toss");
    add_action(throw_pinecone, "lob");
    add_action(throw_pinecone, "hurdle");
    add_action(throw_pinecone, "heave");
}

string
throw_pinecone(string str)
{
    object *oblist;
    string target_loc, target_hurts;

    target_loc = one_of_list(hit_locs);
    target_hurts = one_of_list(hurts);

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    oblist = parse_this(str, "[brown] 'pinecone' [at] %l");

    if (!sizeof(oblist))
    {
        write("Throw "+TO->short()+ " at who?\n");
        return "";
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only throw the "+TO->short()+ " at one "
        	 + "person at the time.\n");
        return "";
    }

     oblist[0]->catch_msg(QCTNAME(TP) + " throws a "+TO->short()+ " at "
     	       + "your "+target_loc+ ". Hitting you "+target_hurts+ ".\n");

     tell_room(ENV(TP), QCTNAME(TP) + " throws a "+TO->short()+ " towards "
        +oblist[0]->query_the_possessive_name(TP) + " direction. Hitting "
        +(oblist[0])->query_possessive()+ " "+target_loc+ " "+target_hurts+ "."
     	+ "\n", ({oblist[0], TP}));

     TP->catch_msg("You throw a "+TO->short()+ " in " 
        + oblist[0]->query_the_possessive_name(TP) + " direction. "
        + "Hitting "+(oblist[0])->query_possessive()+ " " 
        +target_loc+ " "+target_hurts+ ".\n");

     set_alarm(0.1,0.0,&remove_object());
    
    return "";
}
