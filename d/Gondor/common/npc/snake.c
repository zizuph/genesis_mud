/* 
 * This is /d/Gondor/common/npc/snake.c, copied 
 *  in parts from
 *  /d/Gondor/morgul/npc/centipede.c.
 * Olorin, Nov 1994
 *  Use set_poison_frequency to set the rate (in %) how often
 *  the snake tries to poison the enemy
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/trigaction";
inherit "/std/act/domove";

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define A_BITE 0
#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

#define VICTIM_SKILLS	({ TS_DEX, SKILL_AVG, SS_DEFENCE, SS_ANI_HANDL, SKILL_END })
#define SNAKE_SKILLS	({ TS_DEX, SS_UNARM_COMBAT, })

int     frq = 25;
string  poison_file = (POISON_DIR + "snake_poison");

void
create_creature() 
{
   set_name("snake");
   add_name(({"reptile"}));
   set_pname("snakes");
   set_adj(({"poisonous","green"}));
   set_pshort(implode(query_adjs(), ", ") + " snakes");
   set_race_name("snake"); 
   set_long(BSN(
       "A green snake, two or three feet in length, sliding "
     + "rapidly to and fro, hissing dangerously, the long red "
     + "tongue moving in and out of the mouth filled with poisonous "
     + "looking teeth."));
   set_gender(G_NEUTER);
     set_alignment(0); // neutral alignment for animals
   add_prop(CONT_I_WEIGHT,500);
   add_prop(CONT_I_HEIGHT,10);
   add_prop(CONT_I_VOLUME,500);
   add_leftover(NPC_DIR + "snake_meat", "snake meat", 3, 0, 0, 0);
   add_leftover(NPC_DIR + "snake_skin", "snake skin", 1, 0, 0, 0);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(LIVE_I_SEE_DARK,5);

   set_stats(({ 5, 20, 10, 1, 1, 90, }));

   set_skill(SS_UNARM_COMBAT, 60);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_AWARENESS, 25);
   set_skill(SS_BLIND_COMBAT, 70);

   set_attack_unarmed( A_BITE, 70, 10, W_IMPALE,    80, "bite");
   
   set_hitloc_unarmed( H_HEAD, ({ 20, 15, 1}), 10, "head");
   set_hitloc_unarmed( H_BODY, ({ 30, 25, 1}), 80, "body");
   set_hitloc_unarmed( H_TAIL, ({ 20, 15, 1}), 10, "tail");

}

/* For the solamnic Knights */
int query_knight_prestige() { return (100); }

void
do_attack(object victim)
{
    if ((ENV(TO) == ENV(TP)) && (!TP->query_npc()))
        command("kill " +TP->query_real_name());
}

void
init_attack()
{
    if (query_attack())
        return;

    if ((ENV(TO) == ENV(TP)) && (!TP->query_npc())
        && CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO,TP))
        set_alarm(2.0, 0.0, &do_attack(TP));
}

varargs string
poison_bite(object victim)
{
    object  bite;

    if (!objectp(victim))
        victim = TO->query_attack();

    if (!objectp(victim))
        return "";

    if (ENV(TO) != ENV(victim)) 
        return "";

    victim->catch_msg(QCTNAME(TO)+" bites you.\n"+
          "A dreadful chill runs down your spine!\n");
    tell_room(ENV(TO),QCTNAME(TO)+" bites "+QTNAME(victim)+".\n",victim);
    seteuid(getuid(TO));
    bite = clone_object(poison_file);
    bite->move(victim);
    bite->start_poison();
    log_file("curses",victim->query_name()+
        " poisoned by bite of a snake, "+file_name(ENV(TO))
      + ", " + ctime(time())+".\n");

    return "";
}

int
special_attack(object victim)
{
    // How often do we poison?
    if (random(100) >= frq)
        return 1;

    // can the victim evade the deadly bite?
    if (victim->resolve_task(
        TASK_ROUTINE, VICTIM_SKILLS, TO, SNAKE_SKILLS) > 0)
    {
        if (ENV(TO) == ENV(victim))
        {
            victim->catch_msg(QCTNAME(TO)+" tries to bite you, but misses.\n");
            tell_room(ENV(TO),QCTNAME(TO)+" tries to bite "+QTNAME(victim)
              + ", but misses.\n", ({ TO, victim }) );
        }
    }
    else
        poison_bite(victim);
    return 1;
}

void
set_poison_frequency(int i)
{
    frq = i;
}

void
set_poison_file(string p)
{
    if (strlen(p) && ((file_size(p + ".c") > 0) || (file_size(p) > 0)))
        poison_file = p;
}

string
query_poison_file()
{
   return poison_file;
}
