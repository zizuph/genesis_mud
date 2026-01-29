
/**  DARGAARD KEEP ROOM **/

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

inherit GUILD_IN;

object throne = GUILD_ROOM + "throne";
object death_flag;
object player, ob;
object *obj;
string initiate_name;

/* prototypes */
void do_step1();
void do_step2();
void do_step3();
void do_step4();
void do_step5();
void do_step6();
void do_step7();
void do_step8();
void do_step9();
void do_step10();
void do_step11();
void do_step12();
void do_step13();
void do_step14();
void do_step15();
void do_step16();
void do_step17();
void do_step18();
void do_step19();
void do_step20();
void do_step21();
void do_step22();


void
reset_dargaard_room()
{
}

void
create_dargaard_room()
{
    set_short("In an iron cage");
    set_long("You are standing in an iron cage. Below you is a maelstrom of lava. "+
             "The door is closed and locked, you find it impossible to escape.\n");

    reset_dargaard_room();
}


int
start_initiation(object dk)
{

    player = dk;
    initiate_name = QCTNAME(player);

    set_alarm(3.0, 0.0, &do_step1());
    set_alarm(6.0, 0.0, &do_step2());
    set_alarm(9.0, 0.0, &do_step3());
    set_alarm(12.0, 0.0, &do_step4());
    set_alarm(15.0, 0.0, &do_step5());
    set_alarm(18.0, 0.0, &do_step6());
    set_alarm(21.0, 0.0, &do_step7());
    set_alarm(24.0, 0.0, &do_step8());
    set_alarm(27.0, 0.0, &do_step9());
    set_alarm(30.0, 0.0, &do_step10());
    set_alarm(33.0, 0.0, &do_step11());
    set_alarm(36.0, 0.0, &do_step12());
    return 1;
}

void
do_step1()
{
    player->catch_msg("Through the grill you can see fiery lava, swirling in a great "+ 
          "maerlstrom, just waiting to devour you.\n", TO); 
}

void
do_step2()
{
    player->catch_msg("You hear a loud snap, and the cage starts to decent rapidly into "+ 
          "the abyss of fury below the cage.\n", TO);
}

void
do_step3()
{
    player->catch_msg("The iron chains connecting the cage to the ceiling create a loud "+
          "shreaking sound as the cage continues its decent...\n", TO);
}

void
do_step4()
{
    player->catch_msg("The heat starts to burn your hair to a crisp as you approtch "+
          "the surface of the lava.\n", TO); 
    player->heal_hp(-(player->query_max_hp() / 2)); 
}

void
do_step5()
{
    player->catch_msg("Just meters from the maerlstrom, you scream out in pain, as your "+ 
          "skin starts to boil and peel away. Your solamnian armour starts to glow in "+ 
          "an orange colour.\n", TO);
    player->set_hp(0); 
}

void
do_step6()
{
    player->catch_msg("As you hit the molten lava, your blood boils, your skins melts from your bones, and a "+ 
          "last wave of pain washes over you.\n", TO); 
}

void
do_step7()
{
    player->catch_msg("Darkness...\n", TO);
} 

void
do_step8()
{ 
   player->catch_msg("Utter darkness...\n", TO);
}

void
do_step9()
{
    player->catch_msg("Out of the darkness, a red gleam emerges.\n", TO);
}

void
do_step10()
{
    player->catch_msg("Just out of the corner of your eye, you notices two fiery red "+ 
          "eyes, and a gleam of black metal.\n", TO); 
}

void
do_step11()
{
    player->catch_msg("A deep hollow voice rings out in your mind: Come now my "+ 
          "trusted servant. Serve me in this eternal damnation, with furious "+ 
          "loyalty, as you did in life.\n", TO);

    player->catch_msg("Three thoughts bursts forth within you.\n"+ 
          "The Loyalty.\n"+ 
          "The Honour.\n"+ 
          "The Hatred.\n", TO); 
}

void
do_step12()
{
    player->catch_msg("You think you notice a dread smile from the dark figure, just "+ 
          "on the edge of your vision.\n", TO); 

    setuid();
    seteuid(getuid());

    death_flag = clone_object(GUILD_OBJ + "death_flag_join");
    death_flag->move(player);
   
    player->command("$scream");
    player->set_hp(0);
    player->query_hp();
    player->do_die(TO);
}
 

int
end_initiation(object ob)
{
    player = ob;

    set_alarm(6.0, 0.0, &do_step13());
    set_alarm(9.0, 0.0, &do_step14());
    set_alarm(12.0, 0.0, &do_step15());
    set_alarm(15.0, 0.0, &do_step16());
    set_alarm(18.0, 0.0, &do_step17());
    set_alarm(21.0, 0.0, &do_step18());
    set_alarm(24.0, 0.0, &do_step19());
    set_alarm(27.0, 0.0, &do_step20());
    set_alarm(30.0, 0.0, &do_step21());
    set_alarm(33.0, 0.0, &do_step22());
    return 1;
}


void
do_step13()
{
    player->catch_msg("You suddenly feel pulled upwards...\n", TO);
}

void
do_step14()
{
    player->catch_msg("All around you, you notice molten lava burning.\n", TO);
}

void
do_step15()
{
    player->catch_msg("Your armours heats up to an almost bright red colour, "+ 
          "but you feel no pain. You feel nothing.\n", TO);
}

void
do_step16()
{
    player->catch_msg("Suddenly your surroundings accompanied by a roaring "+ 
          "hiss, as you find yourself ascending through endless waters, the "+ 
          "colour of blood.  You notice your armours are cooled down with a roaring hiss, "+ 
          "leaving it blackened in all areas.\n", TO);
}

void
do_step17()
{
    player->catch_msg("Everything turns red as blood, and you feel the bloodlust "+ 
          "running through you...\n", TO);
}

void
do_step18()
{
    player->catch_msg("Slowly the blood fades, and your vision returns.\n", TO); 
}

void
do_step19()
{
    player->catch_msg("You see yourself standing in the black iron cage, being lifted "+ 
          "from the furious lava maerlstrom below you.\n", TO);
}

void
do_step20()
{
    player->catch_msg("The iron cage begins its assent from the lava.\n", TO);
}

void
do_step21()
{
    player->catch_msg("The door to the cage is opened.\n", TO);
}

void
do_step22()
{
    player->catch_msg("Three thoughts ring out in your mind.\n\n"+ 
          "The Loyalty.\n"+ 
          "The Honour.\n"+ 
          "The Hatred.\n", TO); 

    player->catch_msg("You leave the cage.\n", TO);

    player->move_living("M",GUILD_ROOM + "throne");
    throne->become_dk(player);
}

