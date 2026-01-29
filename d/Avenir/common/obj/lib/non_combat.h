/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 * Functions:
 * health_heal()  40% chance of healing random hp amt (gives random messages).
 * poison_cure()  Cures npc of poisons
 *
 */

void 
do_health_heal(object me)
{
    int i, max;

    i = random(10);
    max = me->query_max_hp();

    switch(i)
    {
        case 0: 
        { 
            me->command("emote drinks from a small vial.");
            me->heal_hp(max / 10);
            break;
        }
        case 3: 
        {
            me->command("emote eats a thin trailing vine.");
            me->heal_hp(max / 8);
            break;
        }
        case 6: 
        {
            me->command("emote whispers a word that roars in your ears, "+
                "unintelligible and of great power.");
            me->heal_hp(max / 6);
            break;
        }
        case 9:
        {
            me->command("emote seems to draw on some deep inner reserve "+
                "and attacks with renewed fervor.");
            me->heal_hp(max / 5);
            break;
        }
        default: break;
    }
    return;
}

int
health_heal(string str)
{
    object me = this_player();

    if (!objectp(me))
        return 0;
    
    do_health_heal(me);
        return 1;
}

/* 
 * poison_cure
 */ 
void
do_cure(object me)
{
/*
    int i, rnd;
    object *all;

    all = all_inventory(me);
    for (i=0; i<sizeof(all); i++) 
    {
        if (function_exists("cure_poison", all[i]) ==
            "/std/poison_effect") 
        {
            all[i]->cure_poison(({"all"}), 100);
            me->command("emote sketches a sign in the air.");
            me->command("say Sachluph, I call upon thee!");
            me->command("emote is shrouded briefly in a greenish aura.");
            return;
        }
    }
*/
}

int
poison_cure(string str)
{
    object me = this_player();

    if (!objectp(me))
        return 0;
    
    do_cure(me);
        return 1;
}
