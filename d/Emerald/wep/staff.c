inherit "/std/weapon";
 
#include "/d/Emerald/defs.h"
#include "macros.h"
#include "wa_types.h"
#include "filter_funs.h"
#include "language.h"
 
#define COMBATMSG ({"Ain't I cute?\n","You are foul, I am not!\n",\
                    "I thought you are tougher, chicken.\n",\
                    "Never do it again!\n","Better leave me alone...\n",\
                    "Don't worry, calm down.\n",\
                    "You cannot even beat a chicken!\n"})
#define DAMAGE 300
 
string *feel=({"almost dead",
                  "not quite dead,but almost",
                  "very like dead body",
                  "not looking well at all",
                  "not looking well",
                  "looking rather bad",
                  "hurt",
                  "injured",
                  "a bit scratched",
                  "in the perfect health",
                  "full of life"});
 
 
void create_weapon()
 {
    set_short("black staff");
    set_long("Long black staff made of strange material. It has been "+
             "rumored that it is Grib's property, who is known as "+
             "great magican.\n"+
             "At the top of the staff there is small silver skull, "+
             "probably a human one. The skull has bright shinning "+
             "red eyes which make you shiver in fear.\n");
    set_name("staff");
    set_adj("black");
    set_adj("with");
    set_adj("skull");
    set_pen(35);
    set_hit(45);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE|W_BLUDGEON);
    set_hands(W_BOTH);
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    add_prop(MAGIC_AM_MAGIC,({ 33, "enchantment" }));
 }
 
static void
tell_watcher(string str, object me, object enemy)
 {
    object *ob;
    int i;
 
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
 }
 
int try_hit(object enemy)
 {
    int type;
    int dam;
    object me;
 
    me=query_wielded();
    if (!random(3))
     {
        type=random(6);
        switch(type)
         {
            case 0:
                me->catch_msg("The eyes on the skull flash brightly "+
                              "and staff whispers to you: "+
                              COMBATMSG[random(sizeof(COMBATMSG))]);
                tell_watcher("Eyes of the skull on the "+
                             QTNAME(me)+"'s staff flashes brightly "+
                             "and staff seems to whisper something to "+
                             HIM_HER(me)+".\n",me,me);
            break;
            case 1..2:
                me->catch_msg("Skull on your staff looks deep in your "+
                              "eyes and whispers: 'You might like "+
                              "to know that you're "+
                              feel[me->query_hp()*10/me->query_max_hp()]+
                              ", while you foe is "+
                        feel[enemy->query_hp()*10/enemy->query_max_hp()]+
                              "'.\n");
                tell_watcher("Skull on the "+QTNAME(me)+"'s "+
                             "staff seems to stare at "+HIM_HER(me)+
                             ".\n",me,me);
            break;
            case 3..5:
   dam=me->query_stat(SS_WIS)*DAMAGE/100-enemy->query_stat(SS_DIS)*DAMAGE/250;
                if (dam<0)
                 {
                    me->catch_msg("Skull on your staff tries to bite "+
                                  "your foe, but fails miserably.\n");
                    enemy->catch_msg("Skull on "+QTNAME(me)+"'s staff "+
                                     "bares its fangs and tries to bite"+
                                     " you, striking with fear, but you"+
                                     " manage to avoid it.\n");
                    tell_watcher("Skull on "+QTNAME(me)+
                                 "'s staff bares its"+
                                 " fangs and attempts to bite "+
                                 QTNAME(enemy)+", but fails "+
                                 "miserably.\n",me,enemy);
                 }
                else
                 {
                    me->catch_msg("Skull on your staff bares its fangs "+
                                  "and sinks them into your foe's "+
                                  "body, draining his lifeforces!\n");
                    enemy->catch_msg("Skull on "+QTNAME(me)+"'s staff "+
                                     "bares its fangs and sinks them"+
                                     " deep into your body and drains"+
                                     " your lifeforces!\n");
                    tell_watcher("Skull on "+QTNAME(me)+
                                 "'s staff bares its"+
                                 " fangs and sinks them deep into "+
                                 QTNAME(enemy)+", who howls in pain"+
                                 " !\n",me,enemy);
                    enemy->heal_hp(-dam);
                    me->heal_hp(random(dam));
                    if (!enemy->query_hp())
                     {
                        enemy->do_die(me);
                     }
                 }
            break;
         }
        return 0;
     }
    else return 1;
 }
