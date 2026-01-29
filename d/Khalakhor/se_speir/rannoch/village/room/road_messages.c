/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_messages.c
 * Creator      : Darragh@Genesis
 * Date         : 03-07-26         
 * Purpose      : A module that sends random messages into
 *                occupied road rooms in Abhainn Ruith (west half).
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types
#pragma no_clone

#include "room.h"

inherit "/std/object";

int m_alarm;
int G_x;
int G_y;
float busy_level;

public void give_message();

public void
start_messages(int Gg_x, int Gg_y, float busy)
{
    G_x = Gg_x;
    G_y = Gg_y; 
    busy_level = busy;
    if (get_alarm(m_alarm))
    return;
    m_alarm = set_alarm(10.0 + itof(random(10)), 0.0, give_message);
}

public void
stop_messages()
{
    remove_alarm(m_alarm);
}

public int
filter_to_hear(object ob)
{
    return environment(ob)->is_abhainn_ruith_road();
}

public string
random_message()
{
    int val;

    if (G_x == 7 && G_y == 6)
    {
    val = random(8);

    if (!val)
        return "The air smells horrible here.\n";
    if (val == 1)
        return "The stench of all the garbage on the ground makes you "
             + "feel nauseous and saturated with filth.\n";
    if (val == 2)
        return "An awful stench rises from a puddle of urine mixed "
             + "with what looks like rancid lumps of butter.\n";
    if (val == 3)
        return "You almost faint when you feel the smells of "
             + "animal excrement together with rotten fruit.\n";
    if (val == 4)
        return "The incessant buzz of the flies is beginning to get "
             + "on your nerves.\n";
    if (val == 5)
        return "A boy arrives from the west with a sack slung on his "
             + "shoulder, empties the contents on the ground, and "
             + "leaves west again.\n";
    if (val == 6)
        return "A man arrives from the west with a small cart, tips "
             + "it over in the river, and leaves south.\n";
    if (val == 7)
        return "A man arrives from the south carrying a barrel, empties "
             + "it on the ground, and leaves west.\n";
    return "";
    }
    else
    {

    if (G_x == 4 && G_y == 8) /* Marketplace */
    val = random(75);         /* Extra tells */

    else
    val = random(56);

    if (!val)
        return "You hear the cries of birds from the lake.\n";
    if (val == 1)
        return "You hear the loud cries of birds from the lake.\n";
    if (val == 2)
        return "A breeze comes in from the lake, carrying with it "
             + "a refreshing scent.\n";
    if (val == 3)
        return "A villager walks past, staring thoughtfully at you.\n";
    if (val == 4)
        return "A villager walks past, glaring suspiciously at you.\n";
    if (val == 5)
        return "A man walks past, smiling at you.\n";
    if (val == 6)
        return "A man walks past, swearing to himself.\n";
    if (val == 7)
        return "A man walks past, hauling a cart behind him.\n";
    if (val == 8)
        return "A man walks past, staring at your clothes.\n";
    if (val == 9)
        return "A man runs right past you, dripping with sweat.\n";
    if (val == 10)
        return "A man walks hurriedly past, not noticing you.\n";
    if (val == 11)
        return "A woman walks past, with a look of concern on her "
             + "face.\n";
    if (val == 12)
        return "A woman walks past, carrying a basket of fruit.\n";
    if (val == 13)
        return "A woman walks past, carrying a basket.\n";
    if (val == 14)
        return "A woman walks past, with a child in her arms.\n";
    if (val == 15)
        return "A woman walks past, carrying a basket of eggs.\n";
    if (val == 16)
        return "A woman walks past, not paying any attention to "
             + "you.\n";
    if (val == 17)
        return "You notice a woman wearing a red dress looking at "
             + "you as she walks past.\n";
    if (val == 18)
        return "A woman walks slowly past, with a smile on her face.\n";
    if (val == 19)
        return "A child walks past, with a sad look on her face.\n";
    if (val == 20)
        return "A child walks past, eating a piece of celery.\n";
    if (val == 21)
        return "A child walks past, eating a turnip.\n";
    if (val == 22)
        return "A child walks past, playing with some eggshells.\n";
    if (val == 23)
        return "A child walks past, dragging a small fish in a rope.\n";
    if (val == 24)
        return "A child runs across your path, giggling.\n";
    if (val == 25)
        return "A man and a woman walks past, carrying a sack each.\n";
    if (val == 26)
        return "A man and a woman walks past, hand in hand.\n";
    if (val == 27)
        return "A man and a woman walks past, arguing loudly.\n";
    if (val == 28)
        return "A man and a woman walks past, carrying a dead deer "
             + "between them.\n";
    if (val == 29)
        return "A man and a woman walks slowly by, pulling a cart.\n";
    if (val == 30)
        return "A woman and a child walks past, holding hands.\n";
    if (val == 31)
        return "A woman and a child walks past, wearing filthy clothes.\n";
    if (val == 32)
        return "A woman and a child walks past, sharing a large turnip.\n";
    if (val == 33)
        return "An old man drags himself past you, smelling of alcohol.\n";
    if (val == 34)
        return "An old man walks past, staring at the sky.\n";
    if (val == 35)
        return "An old man drags himself past you, smelling of "
             + "alcohol.\n";
    if (val == 36)
        return "An old man walks by, inspects the closest building, and "
             + "wanders off.\n";
    if (val == 37)
        return "An old woman walks past, singing to herself.\n";
    if (val == 38)
        return "A fisherman walks by, whistling loudly.\n";
    if (val == 39)
        return "A fisherman walks by, wielding a hammer.\n";
    if (val == 40)
        return "A fisherman walks by, carrying a rugged bag.\n";
    if (val == 41)
        return "A fisherman walks by, holding a long fishing pole.\n";
    if (val == 42)
        return "A fisherman walks by, a toothless grin on his face.\n";
    if (val == 43)
        return "A fisherman hurries by, followed by a group of cats.\n";
    if (val == 44)
        return "A fisherman dashes by, followed closely by a group of cats.\n";
    if (val == 45)
        return "A tall hooded woman strides past, carrying a pile "
             + "of pelts.\n";
    if (val == 46)
        return "A slender hooded woman strides across your path, carrying "
             + "a small cage.\n";
    if (val == 47)
        return "A skinny hooded man walks across your path, wielding "
             + "a bow.\n";
    if (val == 48)
        return "A tall hooded man limps past, carrying a stack of "
             + "javelins.\n";
    if (val == 49)
        return "A fisherman walks by, carrying a large fish.\n";
    if (val == 50)
        return "A fisherman walks by, pulling a wheelcart full of fish.\n";
    if (val == 51)
        return "A fisherman hurries by, pulling an empty wheelcart.\n";
    if (val == 52)
        return "A group of cats with a fish each in their mouths slowly "
             + "walk past and into an alley.\n";
    if (val == 53)
        return "A muscular woman strides across your path, carrying "
             + "a pair of oars.\n";
    if (val == 54)
        return "A skinny man walks across your path, carrying "
             + "an oar.\n";
    if (val == 55)
        return "A tall hooded man walks past, carrying a bale of hay.\n";
    if (val == 56)
        return "You stepped in something soft and mushy. Better not "
             + "look down.\n";
    if (val == 57)
        return "A group of children runs in, yelling wildly.\n";
    if (val == 58)
        return "A man arrives with a small covered cart, unloads "
             + "it at the fish merchant, and wanders off again.\n";
    if (val == 59)
        return "A woman arrives carrying two baskets, empties them "
             + "by the egg merchant, and leaves again.\n";
    if (val == 60)
        return "A child wanders in carrying a sack, gives it to "
             + "the poultry merchant, and skips away.\n";
    if (val == 61)
        return "A man across the marketplace carefully inspects "
             + "a bag of apples.\n";
    if (val == 62)
        return "You notice a really ugly old woman, staring right "
             + "at you while eating an onion.\n";
    if (val == 63)
        return "One of the merchants laughs loudly at a customer.\n";
    if (val == 64)
        return "A rat scurries by.\n";
    if (val == 64)
        return "You hear the cries of seabirds to the south of here.\n";
    if (val == 65)
        return "You spot an old man spitting furtively into a huge "
             + "can of milk.\n";
    if (val == 66)
        return "The sound of laughter can be heard west of the "
             + "marketplace.\n";
    if (val == 67)
        return "A young woman arrives from the east with a "
             + "wheelbarrow. She rolls it up to the fruit merchant, "
             + "empties its contents on the ground, and then leaves "
             + "east.\n";
    if (val == 68)
        return "You catch a mixed scent of fish, rotten fruit, and "
             + "the everyday smells of sweat and filth.\n";
    if (val == 69)
        return "You hear someone swearing loudly behind you.\n";
    if (val == 70)
        return "Someone coughs noisily.\n";
    if (val == 71)
        return "Someone laughs loudly nearby.\n";
    if (val == 72)
        return "You notice an old woman stealing a carrot from the "
             + "vegetable merchant.\n";
    if (val == 73)
        return "You notice a group of boys trying to distract one "
             + "of the merchants.\n";
    if (val == 74)
        return "A group of boys whispers among themselves while "
             + "staring at your equipment.\n";
    return "";
    }
}
    
public void
give_message()
{
    object *players;

    players = filter(users(), filter_to_hear);

    if (!sizeof(players))
    {
        stop_messages();
        return;
    }

    players->catch_tell(random_message());

    m_alarm = set_alarm(busy_level + itof(random(120)), 0.0, give_message);

}        
