/* a skunk that squirts you
* coded by Stevenson
*/

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#define STINK_OBJ "/d/Krynn/solace/village/obj/stink"

inherit C_FILE
inherit "/std/act/domove";
inherit "/std/act/action";

void
init_living() 
{
    write("You smell a skunk!\n");
    if (random(100) > 95)
      set_alarm(1.0,0.0,"random_spray",TP);
    ::init_living();
}

void
create_creature() 
{
    int i;
    set_short("skunk");
    set_race_name("skunk");
    set_name("skunk");
    set_long("It is a small skunk. It is covered in black fur with a long "
	     + "white stripe up its back. He really is quite a little "
	     + "stinker.\n");
    
    for (i=0;i<6;i++)
      set_base_stat(i, 10+random(5));
    
    set_skill(SS_DEFENCE, 15);
    set_knight_prestige(0);
    set_alignment(0);
    
    set_hp(query_max_hp());
    set_alarm(1.0,0.0,"set_restrain_and_home",0);
    set_random_move(20);
    
    set_act_time(2);
    add_act("emote digs in the ground, searching for bugs.");
    add_act("emote smells some flowers.");
    add_act("emote sticks its tail up into the air.");
    add_act("emote looks up at you with panic in its eyes.");
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(CONT_I_VOLUME, 300);
    add_prop(CONT_I_WEIGHT,700);
    
    set_attack_unarmed(0, 10, 10, W_IMPALE, 60, "bite");
    set_attack_unarmed(1, 7, 8, W_SLASH, 40, "claw");
    
    set_hitloc_unarmed(0, 5, 30, "head");
    set_hitloc_unarmed(1, 5, 30, "tail");
    
    seteuid(getuid(TO));
}

int
do_spray(object ob)
{
    if (!CAN_SEE(TO,ob))
      return 0;
    if (!P("stink",ob))
      clone_object(STINK_OBJ)->move(ob);
    return 1;
}


void
do_die(object ob) 
{
    if (query_hp() <= 0 && interactive(ob))
      if (do_spray(ob))
	{
	    write("In a last effort the skunk sprayed you!\n");
	    tell_room(E(TO),"In a last effort, the skunk squirted " +
		      QTNAME(ob) + ".\n",ob);
	}
    ::do_die(ob);
}

/* Function:    set_restrain_and_home
 * Arguments:   depth <= 0 use the direct subdir of the monster_home
 *                         as restrain path.
 *                     > 0 go depth subdirs up in the directory list
 *                         for the restrain path.
 * Description: I set my own restrain path and home according to where
 *              I start. The restrain path will only be the subdir
 *              where the home is located. To specify a higher dir
 *              as restrain path, use the depth parameter.
 *              Call this function after cloning with an alarm > 1 if
 *              you want to set the depth to a different value.
 * Returns:     void
 */
void
set_restrain_and_home(int depth)
{
    string path = file_name(E(TO));
    string *parts = explode(path,"/");
    if (depth < 0)
      depth = 0;
    parts = parts[0..sizeof(parts)-2-depth];
    set_restrain_path(implode(parts,"/"));
    set_monster_home(file_name(E(TO)));
}

void
random_spray(object ob) 
{
    if (ob->query_skill(SS_ANI_HANDL) > 20)
      return;
    if (!ob || E(ob) != E(TO))
      return;
    if (!do_spray(ob))
      return;
    ob->catch_msg("The skunk sprays you.\n");
    tell_room(E(ob),"The skunk suddenly sprays " +
	      QTNAME(ob)+".\n", ob);
}
