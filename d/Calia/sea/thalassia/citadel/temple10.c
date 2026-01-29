
/*  Diabrecho Temple in Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar
                19. 7.03    added descriptions for          Jaacar
                            Worshippers praying to the 
                            statue, start of quest to
                            become a member of the Spirit
                            Circle of Psuchae.
*/

#pragma save_binary
#pragma strict_types

inherit "/d/Calia/std/water_room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include SEA_QUESTS
#include WORSHIP_HEADER

void
create_water_room()
{
    set_short("An altar in the Temple of Diabrecho");
    set_long("You are swimming in the magnificent Temple of Diabrecho. "+
        "This structure was built originally to house statues of the "+
        "leaders of the city, but was later changed to show thanks "+
        "to Lord Diabrecho for the gift of life in the sea. Rising "+
        "up before you is a gigantic golden statue of Lord Diabrecho "+
        "riding in a chariot drawn by six massive sea-horses. "+
        "Surrounding the chariot and sea-horses are one hundred golden "+
        "statues of tritons riding dolphins. The statue of Lord "+
        "Diabrecho is so large that its head touches the top of the "+
        "domed roof. There is a large altar here, directly "+
        "in front of the statues. Surrounding the outside walls of the "+
        "temple are statues of the past leaders of this city, also made "+
        "of gold. There are many pillars rising up to hold the ceiling "+
        "in place above you. There is a pathway leading north and south "+
        "from here.\n");

    add_item(({"altar","large altar"}),"This large altar is constructed "+
        "of the fiery metal orichalcum and decorated with white marble. "+
        "Etched in silver is the name \"Lord Diabrecho\". The altar is "+
        "placed directly in front of the gold statues. You deduce that "+
        "this altar must be used for ceremonies of great importance "+
        "here in the city.\n");

    add_item("pathway","The pathway leads off to the north and south.\n");

    add_item(({"wall","walls","outside wall","outside walls"}),
        "The walls are made entirely of gold blocks placed one on "+
        "top of the other. The seams between the blocks are so "+
        "small that it is almost impossible to see them, giving "+
        "the illusion that the wall is one solid mass of gold.\n");

    add_item(({"pillar","pillars"}),"These silver coated pillars rise "+
        "up two hundred feet to hold the golden ceiling above you. "+
        "Each one is perfectly round and smooth.\n");

    add_item(({"roof","ceiling","dome","domed roof"}),"The roof is "+
        "made entirely of gold except for the dome which rises "+
        "another one hundred feet above the rest of the roof. The "+
        "inside of the dome is coated in white ivory slabs between "+
        "which run veins of orichalcum, silver and gold. The head "+
        "of the statue of Lord Diabrecho touches the middle of the "+
        "the dome.\n");

    add_item(({"triton","tritons","triton statue","triton statues"}),
        "The golden triton statues each depict a muscular creature "+
        "with a human-like torso and arms but from the waist down "+
        "they have tails like that of a fish which are wrapped "+
        "around the bottom of the dolphin statues they are riding. "+
        "Each one is wielding a trident in both hands.\n");

    add_item(({"sea-horse","sea-horses","sea horse","sea-horses",
        "sea-horse statue","sea-horse statues","sea horse statue",
        "sea horse statues"}),"These massive golden sea-horses dwarf "+
        "all but the largest of their land-based cousins. They are "+
        "so muscular in fact that you think that just one of these "+
        "beasts could pull this entire chariot on its own.\n");

    add_item(({"chariot","chariot statue"}),"This gigantic golden "+
        "statue is a beautifully decorated chariot. Riding inside of the "+
        "chariot is Lord Diabrecho. There are six massive sea-horses "+
        "pulling this chariot.\n");

    add_item(({"leader","leaders","leader statue","leader statues"}),
        "These marvelous golden statues of the past leaders of "+
        "Thalassia were carved by the hands of the finest sculptors "+
        "in the entire city and then carefully coated in gold. There "+
        "are ten statues in all.\n");

    add_item(({"statue","statues","gold statue","gold statues"}),
        "Which statue(s) do you want to look at? The statue of "+
        "Lord Diabrecho, the dolphin statue(s), the triton statue(s), "+
        "the sea-horse statue(s), the chariot statue, or the leader "+
        "statue(s)?\n");

    add_item(({"dolphin","dolphins","dolphin statue","dolphin statues"}),
        "These golden dolphin statues seem to float magically around "+
        "the statue of Lord Diabrecho, each with a triton rider on its "+
        "back.\n");

    add_item(({"Lord Diabrecho","lord diabrecho","diabrecho",
        "Diabrecho","statue of Lord Diabrecho",
        "statue of lord diabrecho"}),"This massive golden statue of "+
        "Lord Diabrecho must be over one hundred and fifty feet in "+
        "length and three hundred feet tall at its highest point. "+
        "He is very handsome, with rich and flowing hair and a sleek "+
        "yet muscular body. He stands in a chariot of gold wielding "+
        "a giant trident in one hand and holding the reigns to the "+
        "sea-horses in the other.\n");

    IN;

    add_swim_exit(THALC+"temple9","north",0,1);
    add_swim_exit(THALC+"temple11","south",0,1);
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

int
do_pray(string str)
{
    if ((!str) || (str != "to Lord Diabrecho"))
    {
        NF("Pray to whom? Lord Diabrecho perhaps?\n");
        return 0;
    }

    if (TP->is_worship() && !(TP->query_prop(LIVE_I_PRAYED_AT_DIABRECHO_ALTAR)))
    {
        write("You begin to pray to Lord Diabrecho with all of your "+
            "heart and soul. You quickly become dizzy as the room "+
            "appears to begin swirling rapidly around you. It becomes "+
            "difficult to see as your eyes glaze over. As quickly as it "+
            "came over you, the feeling stops and everything is clear "+
            "again. You look up at the statue of Lord Diabrecho and "+
            "notice it has changed, Lord Diabrecho is alive! He glances "+
            "downward at you, smiling. He extends his large hand towards "+
            "you and gently touches your head briefly. In a gentle voice "+
            "you hear him speak,\n\n"+
            "\"Welcome my child. It is good to be able to lay my eyes "+
            "upon you in person. Go forth and spread the blessings of "+
            "the Elementals. Go forth and find glory in our teachings. "+
            "Go forth and embrace the destiny that awaits you.\".\n\n"+
            "The feeling of dizziness returns, your eyes blur over, "+
            "everything is spinning again. The feeling stops, you look "+
            "back to the statue and everything has returned to how it "+
            "originally was. The statue is just that, merely a statue "+
            "once again.\n");
        TP->add_prop(LIVE_I_PRAYED_AT_DIABRECHO_ALTAR,1);
        say(QCTNAME(TP)+" prays at the altar. "+capitalize(HIS(TP))+" eyes "+
            "glaze over but quickly return to normal after just a few "+
            "moments.\n");     
        return 1;
    }
    
    write("You begin to pray to Lord Diabrecho. You feel a presence "+
          "come over you, a strong presence. You glance up at the eyes "+
          "of the statue and you somehow know they are watching you. "+
          "You sense an inner peace come over you.\n");
    say(QCTNAME(TP)+" prays at the altar.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_pray,"pray");
}
