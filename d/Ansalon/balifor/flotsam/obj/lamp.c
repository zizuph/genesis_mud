/* by Gorr 19/12/96 */
/* updated 21/12/96 */

inherit "/std/object";
#include <macros.h>
#include "../local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"

int lamp_alignment = random(1);
int lamp_al;
object pris;
string bottom();
int djinn_released = 0;
int imprisoned = 0;
object djinn_npc;
object come_room;
object prisoner;

/* lamp_alignment : 0 - only evil can rub lamp
 *                  1 - only good can rub lamp
 */

void
create_object()
{
    set_name("lamp");
    set_adj("old");
    add_adj("shining");
    set_short("old shining lamp");
    set_long("@@long_desc");

    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_M_NO_SELL,"Hmmm ... You better keep the lamp.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This is a magic lamp, enchanted " +
             "by some renegate mage from nomad tribe. A Djinn " +
             "Azarel can be summoned from it by rubbing the lamp. " +
             "But only a player with adequate alignment can free the " +
             "Djinn or player imprisoned in a lamp.\n",15}));
    add_item("inscription","@@inscription");

    add_cmd_item("inscription","read","@@inscription");
    add_cmd_item("lamp","rub","@@rub_lamp");
}

string
long_desc()
{
    return"This shining oil lamp seems to be more piece of art than " +
          "a source of light. Beautiful, exotic ornaments adore its " +
          "walls. They depict some people living on the desert." +
          bottom();
}

string
bottom()
{
    if(TP->query_skill(SS_AWARENESS) < 30)
     return"";
    else
     return" On the bottom of the lamp you catch a glimpse of a " +
           "faint inscription.\n";
}

string
inscription()
{
    if(TP->query_skill(SS_AWARENESS) < 30)
    {
        write("You dont find any inscription.\n");
    }
    else
    {
        if(lamp_alignment == 0)
        {
         write("The inscription says: Only those corrupted enough can " +
              "free my prisoner.\n");
        }
        else
        {
         write("The inscription says: Only those holy enough can " +
              "free my prisoner.\n");
        }

    }
    return"";
}

string
rub_lamp()
{
    if(((TP->query_alignment() > 100) && (lamp_alignment == 1)) || ((TP->query_alignment() < -100) && (lamp_alignment == 0)))
    {
        write("You rub the lamp and it glows brightly.\n");
        say(QCTNAME(TP) + " rubs the lamp and it glows brightly.\n");
        if((djinn_released == 1) && (imprisoned == 0))
        {
            return"";
        }
        if(djinn_released == 0)
        {
            set_alarm(10.0,0.0,"djinn_comes");
            return"";
        }
        set_alarm(10.0,0.0,"prisoner_comes");
        return"";
    }
    else
    {
        write("You rub the lamp but nothing happens.\n");
        say(QCTNAME(TP) + " rubs the lamp but nothing happenes.\n");
        return"";
    }
}

void
djinn_comes()
{
    come_room = E(TO);
    if(living(E(TO))) come_room = E(E(TO));
    if(!living(E(TO)) && living(E(TO))) come_room = E(E(E(TO)));

    say("Suddenly the multicoloured smoke starts comming from the lamp. " +
        "It slowly forms a humanoid shape.\n");
    write("Suddenly the multicoloured smoke starts comming from the lamp. " +
        "It slowly forms a humanoid shape.\n");
    djinn_npc = clone_object(FNPC + "djinn.c");
    djinn_npc->set_lamp(TO);
    djinn_npc->move(come_room);
    djinn_npc->command("emote hollows: Greetings Mortal !");
    djinn_released = 1;
}

void
prisoner_comes()
{
    come_room = E(TO);
    if(living(E(TO))) come_room = E(E(TO));
    if(!living(E(TO)) && living(E(TO))) come_room = E(E(E(TO)));

    say("Suddenly the multicoloured smoke starts comming from the lamp. " +
        "It slowly forms a shape of " + prisoner->query_race() + ".\n");
    write("Suddenly the multicoloured smoke starts comming from the lamp. " +
        "It slowly forms a shape of " + prisoner->query_race() + ".\n");
    prisoner->catch_msg("You feel some magic force pushing you out of the " +
              "lamp. A moment later you are free but you still feeling " +
              "strange.\n");
    prisoner->move(come_room);
    imprisoned = 0;
}

/*
 * Lets mask this function to set owner to Djinn every time
 * the lamp changes its owner
 */

void
enter_env(object inv, object from)
{
    djinn_npc->set_owner(inv);
    if(!living(inv) && living(E(inv)))
     djinn_npc->set_owner(E(inv));
    ::enter_env(inv, from);
}

/* A function allowing other object to set prisoner */

void
set_prisoner(object pris)
{
    prisoner = pris;
    imprisoned = 1;
}

/* A function allowing other object to change lamp_alignment */

void
set_lamp_al(int set_al)
{
    lamp_alignment = set_al;
}

/* A function allowing other object to get info on lamp alignment */

int
query_lamp_al()
{
    return lamp_alignment;
}
