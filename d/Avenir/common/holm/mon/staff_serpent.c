// -*-C++-*-
// Serpent of the Staff    /d/Avenir/common/holm/mon/staff_serpent.c
// creator(s):     Lilith  10 Feb 1997
// last update:  
// purpose:        This is the serpent that is cloned when the staff
//                 enters an non-living environment. The serpent
//                 re-clones the staff (/holm/obj/serpent_staff.c)
//                 when it enters a living.
// note:          Benefits:
//                -If the owner/dropper is in combat when the staff
//                 is dropped, the serpent will attack his enemies.
//                 (I'm not sure how to calculate its combat aid.)
//                -The serpent can be easily handled by its owner.
//                Drawbacks:
//                -The serpent can be picked up by anyone who has
//                 the right combination of skills.
//                -There is a 30 minute delay before the staff can 
//                 be dropped again to form a serpent.
//                -If the serpent is killed the staff is broken.
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
#include "../holm.h"
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>

#define SNAKESTAFF   HOLM_OBJ + "serpent_staff"
#define SNAKEPROP    "_Avenir_snake_staff"
#define SNAKEALT     HOLM_OBJ + "staff_alt"
string own;

string query_owner()          {    return own;    }
void   set_owner(string str)  {    own = str;     }
void   help_owner(object owner);

void
create_creature()
{
    if (!IS_CLONE)
        return;
    set_name("serpent");
    add_name("Serpent_of_the_Staff");
    set_race_name("serpent");
    set_gender(G_MALE);
    add_adj(({"brown", "large"}));
    set_long("This serpent is large and brown, with formidable fangs. The "+
       "coloration of his scales resembles the grain and lustre of polished "+
       "wood. It has a nasty-looking barb on its tail.\n");
  
    default_config_creature(50 + random(10));
   // It is very quick, but I didn't want to inflate the kill exp, so...
    set_stat_extra(SS_DEX, 100); 
    add_prop(LIVE_I_QUICKNESS, 80 + random(25));
    set_alignment(-(50 + random(100)));

     //        'weapon', hit, pen, damage type, %use, desc                      
    set_attack_unarmed(1, 30, 35, W_SLASH,     25, "barbed tail");
    set_attack_unarmed(2, 20, 45, W_IMPALE,    50, "fangs");
    set_attack_unarmed(4, 15, 20, W_BLUDGEON , 25, "head");
    //             where, ac, %hit, desc
    set_hitloc_unarmed(1,  40, 10, "body");
    set_hitloc_unarmed(2,  40, 10, "head");
    set_hitloc_unarmed(4,  10, 10, "left eye");
    set_hitloc_unarmed(8,  10, 10, "right eye");
    set_hitloc_unarmed(16, 45, 10, "tail");

    set_skill(SS_DEFENCE, 60);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_BLIND_COMBAT, 70);

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(CONT_I_MAX_VOLUME, 1100);
    add_prop(CONT_I_MAX_WEIGHT, 1100);
    add_prop(OBJ_I_RES_FIRE, 50);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(OBJ_M_NO_GET, "@@get_check@@");

    seteuid(getuid());
}

int
special_attack(object victim)
{
    object me;
    string *randhit = ({"thigh", "head", "back", "buttocks", "hand", "forearm"});
    int how;
    mixed where;

    if(random(3)) return 0; /* normal attack */

    me = this_object();
    how = (random(sizeof(randhit)));    
    where = randhit[how];
    switch(random(2))
    {
        case 0:
            victim->catch_msg(QCTNAME(me) + " tears at you with with "+
                "his needle-sharp fangs!\n");
            tell_watcher(QCTNAME(me) +" tears into "+ QTNAME(victim) +
                " with his needle-sharp fangs!\n", victim);
            victim->heal_hp(-(20 + random(20)));
            break;
        case 1:
            victim->catch_msg(QCTNAME(me) +" grazes your "+ where +
                " with his barbed tail!\n");
            tell_watcher(QCTNAME(me)+ " grazes " + QTPNAME(victim) +
                " "+ where +" with his barbed tail!\n", victim);
            victim->heal_hp(-(10 + random(10)));
            break;
    }
    return 1;
}

/*
 * help_owner is called from the staff when it clones this object.
 * If the 'owner' is in combat, the serpent will join in.
 */
void
help_owner(object owner)
{
    object *foes, foe;
    int i;
  
    if (!query_owner())
      return;

    foes = owner->query_enemy(-1);
    for (i=0; i<sizeof(foes); i++) 
    if (objectp(foe = foes[i]) && environment() == environment(foe)) 
    {
        add_prop(NPC_I_NO_FEAR, 1);
        command("kill " + foe->query_real_name());
    }
}

/*
 * get_check determines whether or not the serpent 
 * can be gotten by a player.
 */
int
get_check()
{
    int stask;

    if (TP->query_real_name() == TO->query_owner())
    {
        write("The serpent seems to welcome your hands upon it and "+
            "does not try to evade your grasp. You succeed in "+
            "getting the serpent.\n");        
        return 0;
    }
    stask = TP->resolve_task(TASK_FORMIDABLE, ({TS_DEX, SS_ANI_HANDL}));
    if (stask > 0)
    {
        write("You are quick enough to grasp the serpent with "+
            "one hand behind its head and the other near its "+
            "tail.\n");
        say(QCTNAME(TP) +" wrestles with the serpent and "+
            "succeeds in picking it up.\n");
        return 0;
    }
    else
    {
        write("The serpent wriggles out from under your grasp"+
            "ing hands. You fail to get the serpent.\n");
        return 1;
    }
} 

/*
 * transform is called by the enter_env
 */
void 
transform(object inv)
{
    object staff;

    write("The large brown serpent stiffens in your hands and "+
        "is suddenly transformed into a wooden staff carved in "+
        "its own likeness!\n");

    staff = clone_object(SNAKESTAFF);
    staff->remove_magic();
    staff->move(ENV(TO), 1);     
    remove_object();
}


/* 
 * Controls transformation back into a staff 
 */
void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);    

    /* If in a room, stay a snake */
    if (inv->query_prop(CONT_I_IN) && inv->query_prop(ROOM_I_IS))
        return;      

    /* Otherwise transform to a staff */
    else
    {
        set_alarm(1.0, 0.0, &transform(inv));    
        return;
    }
    return;
}

/* 
 * When snake is killed, it is transformed back into a staff,
 * but a broken one.
 */
void
do_die(object killer)
{
    string *killers;
    object staff;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    staff = clone_object(SNAKEALT);
    staff->move(ENV(TO), 1);
    staff->add_prop(OBJ_I_BROKEN, 1);

    ::do_die(killer);
}

int
query_knight_prestige() { return 100; }

