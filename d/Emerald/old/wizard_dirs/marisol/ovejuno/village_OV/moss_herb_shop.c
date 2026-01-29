/*
 *
 * coded by Amelia for Ten Alders 4/13/97
 * specials:  when witch apprentice present, buys and
 *            sells herbs can also buy an herb jar or 
 *            pouch here
 * Modified by Marisol to be used in the new Re Albi as 
 * Moss's herb shop and house. (2/21/98)
 */

inherit "/d/Earthsea/std/room";
inherit "/sys/global/money.c";

#pragma no_clone
#pragma strict_types

#include <defs.h>
#include <stdproperties.h>
#include "defs.h"
#include "/d/Earthsea/sys/macros.h"
#include <cmdparse.h>
#include <macros.h>       
#include <money.h>

#define HERBALIST RA_VILLAGE_NPC+"moss.c"
#define JAR_RA    HERB_OBJ+"herb_jar.c"
#define PO_RA     HERB_OBJ+"herb_pouch.c"
#define DOOR_N    DOORS+ "moss_out"


mixed          *storedherbs = ({});

object          herbalist;

object door_n;


void
reset_room()
{
    if (!objectp(herbalist))
    {                                                            
        herbalist = clone_object(HERBALIST);
        herbalist->move(TO);
        herbalist->arm_me();
        herbalist->command("emote enters the store "+
          "and sits on the stool.");
    }

    seteuid(getuid(this_object()));
    save_object(HERB_DIR+"herbfile");
}

void
create_earthsea_room()
{

    set_short("Moss's herb shop");
    set_long("Moss's herb shop also serves as her "+
        "home together with her chickens. A musty smell fills "+
        "the house. Chickens walk in and out of the hut. You "+
        "can hear their cacophony all around you. In the roof "+
        "you can see chickens resting between the beams, and herbs "+
        "hanguing down drying to be used later. There are shelves "+
        "resting in the walls full of jars of different herbs and "+
        "spices. Although Moss is considered an old filthy-looking "+
        "witch, she is, after all, the only witch that the villagers "+
        "have and a good one, all things consider. She is also a "+
        "midwife and bone-setter so she always has work to do. "+
        "She can provides you with any herbs or paraphernalia "+
        "that you need.\n"); 


    add_item("jars", 
      "The jars on the shelves seem to contain all sorts of "+
      "herbs and spices that you can't even begin to fathom. Moss "+
      "seems to know a lot about her business.\n");

    add_item((({"shelf", "shelves"})),
      "The wooden shelves run the lengths of three walls "+
      "and extend from floor to ceiling. They are loaded with "+
      "big and small bottles, jars, and other containers.\n");

    add_item("ceiling",                                                   
      "You can see the chickens peeking out in between "+
      "the wooden beams that hold the thatched roof. "+
      "The beams run along the ceiling, where herbs "+
      "of all kinds have been hung to dry.\n");

    add_item("floor",
      "The floor is sunk below ground level, and "+
      "is comprised of hard-packed earth. It is "+
      "covered with discared feathers from the roaming "+
      "chickens and some other stuffs quite fragant and well "+
      "just a little disgusting. Just be careful where you step.\n");

    add_item((({"wall", "walls"})),
      "The walls are made of discared wood panels.\n");

    add_item((({"beams", "beam", "bundles", "bundle"})),
      "Bundles of drying herbs hang down from the wooden "+
      "beams in the ceiling.\n");

    add_item((({"herb", "herbs"})),
      "Herbs of all kinds fill this room with "+
      "diverse piquant aromas.\n");

    door_n = clone_object(DOOR_N);
    door_n->move(TO);

    add_item("sign", "The sign reads:\n" +
      "------------------------------\n" +
      " Here you can - list herbs  \n" +
      "              - list equipment\n" +
      "              - sell herbs    \n" +
      "              - buy equipment     \n" +
      "              - buy herbs     \n");
    restore_object(HERB_DIR+"herbfile");
    reset_room();
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);
    add_prop(ROOM_I_INSIDE, 1);

}                                                                        
void
init()
{

    ::init();
    add_action("read_sign", "read");
    add_action("sell_herb", "sell");
    add_action("list_herb", "list");
    add_action("buy_herb", "buy");
}
int
read_sign(string str)
{

    notify_fail("Read what?\n");
    if (str == "sign")
    {
        TP->catch_msg("The sign reads:\n" +
          "------------------------------\n" +
          " Here you can - list herbs \n" +                  
          "              - list equipment\n" +
          "              - sell herbs    \n" +
          "              - buy equipment     \n" +
          "              - buy herbs     \n");
        return 1;
    }
    return 0;
}


/*
 *  sell_herb allows a player to sell an herb in the store
 *  if it has an herb name.
 *  Herbalist must also be present.
 *  'pays' a player, and adds the herb to the stored herbs
 */
int
sell_herb(string str)
{
    int             invnr, htsize, herbvalue, storesize;             
    int             exist;
    int             amount;
    mixed           herbpath;
    object         *htsell;
    object          herb;
    string          herbname;
    string           hn;

    herbalist = find_living("_moss_");

    // Check for presence of herbalist, before allowing player to sell

    if (!objectp(herbalist))
    {
        notify_fail("No one is here to buy your herbs.\n");
        return 0;
    }
    storesize = sizeof(storedherbs);
    if (str == "") {
        notify_fail("Sell which herb?\n");                  
        return 0;
    }
    htsell = FIND_STR_IN_OBJECT(str, TP);
    htsize = sizeof(htsell);

    if (htsize == 0) {
        TP->catch_msg("You don't have any " + str + ".\n");
        return 1;
    }
    for (invnr = 0; invnr < htsize; invnr++)
    {
        if (stringp(htsell[invnr]->query_herb_name()))
            hn = htsell[invnr]->query_herb_name();
        else
        if (sizeof(htsell[invnr]->query_herb_name()))
            hn = (htsell[invnr]->query_herb_name())[0];
        if (stringp(hn))
        {
            herb = htsell[invnr];
            herbname = hn;                                
            herbvalue = herb->query_herb_value();
            herbpath = MASTER_OB(herb);

            for (exist = 0; exist < storesize; exist = exist + 4)
            {
                if (storedherbs[exist] == herbname)
                {
                    if (storedherbs[exist + 3] < 100)
                    {
                        storedherbs[exist + 3] = (storedherbs[exist + 3] + 1);
                    }
                    add_money(herbalist, (herbvalue/2));
                    herbalist->command("say Ah, yes. I will buy your "+
                      herbname + ".");
                    herbalist->command("give coins to "+
                      lower_case(TP->query_name()));
                    herb->remove_object();
                    return 1;
                }
            }                                             
            storedherbs += ({herbname});
            storedherbs += ({herbpath});
            storedherbs += ({herbvalue});
            storedherbs += ({1});
            add_money(herbalist, herbvalue);

            herbalist->command("say Yes, I will purchase your "+
              herbname+".");
            herbalist->command("give coins to " +
              lower_case(TP->query_name()));


            herb->remove_object();
            return 1;
        }
    }
    herbalist->command("say You don't have any herb "+
      "called "+ str + " to sell.");
    herbalist->command("eyebrow");
    return 1;                         
}

int
list_herb(string str)
{
    int             nr, herbvalue, number, herbnr;
    string          herbname;
    object          herb_file;

    notify_fail("List what? Herbs or equipment?\n");
    herbalist = find_living("_moss_");

    if (!objectp(herbalist))
    {
        notify_fail("The witch's apprentice is not here.\n");
        return 0;
    }

    if (str == "equipment" || str == "equip") {
        herbalist->command("smile");                            
        herbalist->command("hmm");
        herbalist->command("say You may buy the following "+
          "equipment here.");
        herbalist->command("say A nice herb jar for 300 cc");
        herbalist->command("say A leather pouch for 200 cc");
        return 1;
    }
    if (str == "herbs")
    {
        herbalist->command("say I have the following herbs in stock "+
          "now.");
        herbalist->command("hmm");
        if (!sizeof(storedherbs))
        {
            herbalist->command("say I am out of herbs at the moment.");
            return 1;
        }
        herbnr = sizeof(storedherbs);

        if (herbnr > 0)                                     
            for (nr = 0; nr < herbnr; nr = nr + 4) {
                herb_file = call_other(storedherbs[nr+1], "load_me");
                if (!objectp(herb_file))
                {
                    herbname = storedherbs[nr];
                    herbvalue = storedherbs[nr + 2];
                    number = storedherbs[nr + 3];
                    herbalist->command("say I have "+ number +
                      " "+ herbname + " for "+
                      herbvalue + " copper coins each.");
                }
            }
        return 1;
    }
    return 0;
}

int
buy_herb(string str)
{                                                              
    object          dummy;
    object          boughtherb;
    int             nr, herbnr;

    notify_fail("Buy what?\n");

    herbalist = find_living("_moss_");

    if (!objectp(herbalist))
    {
        notify_fail("Moss is not here.\n");
        return 0;
    }

    if ((str) && (objectp(herbalist)))
    {


        if (str == "jar")
        {                                                      
            if (take_money(TP, 300) == 0)
            {
                TO->no_afford(TP);
                return 1;
            }
            TP->catch_msg("You pay " + QTNAME(herbalist) + ".\n");
            say(QCTNAME(TP) + " pays " + QTNAME(herbalist) + ".\n");
            dummy = clone_object(JAR_RA);
            dummy->move(herbalist);
            herbalist->command("give jar to "+
              lower_case(TP->query_name()));
            return 1;
        }

        if (str == "pouch")
        {
            if (take_money(TP, 75) == 0)
            {
                TO->no_afford(TP);
                return 1;                      
            }
            TP->catch_msg("You pay " + QTNAME(herbalist) + ".\n");
            say(QCTNAME(TP) + " pays " + QTNAME(herbalist) + ".\n");
            herbalist = find_living("_moss_");
            dummy = clone_object(PO_RA);
            dummy->move(herbalist);
            herbalist->command("give pouch to " +
              lower_case(TP->query_name()));
            return 1;
        }

        if (!sizeof(storedherbs))
        {
            herbalist->command("say I have no herbs in stock "+
              "right now, dearie.");
            return 1;
        }
        if (str == "herb" || str == "herbs")
        {
            herbalist->command("say You need to be more specific."); 
            herbalist->command("say There are many herbs.");
            return 1;
        }
        herbnr = sizeof(storedherbs);

        for (nr = 0; nr < herbnr; nr = nr + 4)
        {
            if (storedherbs[nr] == str)
            {
                if (storedherbs[nr + 3] > 0)
                {
                    herbalist->command("say Here is a "+
                      str + " for you, dearie!");
                    herbalist->command("say That will be " +
                      storedherbs[nr + 2 ] +
                      " copper coins.");
                    if (take_money(TP, storedherbs[nr + 2]) == 0)
                    {
                        TO->no_afford(TP);
                        return 1;                            

                    }
                    TP->catch_msg("You pay and get your " + str + ".\n");
                    say(QCTNAME(TP) + " pays and gets " +
                      TP->query_possessive() +
                      " " + str + ".\n");
                    boughtherb = clone_object(storedherbs[nr + 1]);

                    boughtherb->move(TP);
                    herbnr = herbnr - 1;
                    if (storedherbs[nr + 3] > 1)
                        storedherbs[nr + 3] = (storedherbs[nr + 3]) - 1;
                    else
                        /* delete herb from object file */
                    if (storedherbs[nr + 3] == 1)
                    {
                        if (nr == 0)
                        {
                            storedherbs = storedherbs[(nr + 4) .. herbnr];
                            return 1;
                        }             
                        if (nr == (herbnr - 3)) {
                            storedherbs = storedherbs[0..(herbnr - 4)];
                            return 1;
                        }
                        storedherbs = storedherbs[0..(nr - 1)] +
                        storedherbs[(nr + 4) .. herbnr];
                        return 1;
                    }
                    return 1;
                }
                herbalist->command("say I don't have any "
                  + str + " in stock.");
                return 1;
            }
        }
        herbalist->command("say I don't have any " + str + " in stock.");
        return 0;
    }
    return 0;
}                                                               

void
remove_object()
{
    seteuid(getuid(this_object()));
    save_object(HERB_DIR+"herbfile");
    ::remove_object();
}


int
no_afford(object who)
{
    int             act;
    act = random(3);

    herbalist = find_living("_moss_");
    if (act == 0)
    {
        herbalist->command("say You can't afford that much!"); 
        herbalist->command("poke " + who->query_name());
        return 1;
    }
    if (act == 1)
    {
        herbalist->command("say So sorry, but you "+
          "do not seem to have enough money, dearie.");
        herbalist->command("peer "+ lower_case(TP->query_name()));
        return 1;
    }
    herbalist->command("hmm");
    herbalist->command("say I'm not doing charity!");
    herbalist->command("say No money no honey!.");
    herbalist->command("nudge " + lower_case(who->query_name()));
    return 1;
}                                                            
