/*
 * Red rose from the garden of Telseron
 * Coded by Finwe, October 1996
 */
 
inherit "/d/Emerald/telseron/flowers/flowers.c";
#include "/sys/language.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
 
public void
create_flower()
{
 
    set_name("rose");
    set_short("flower");
    set_short("rose");
    set_pname("roses");
    set_fragrance(1);
    set_adj("perfect");
    set_long("A beautiful long-stemmed rose. It is a deep red colour. " +
        "Few flowers display one's devotion like that of a red rose. " +
        "The bearer of this beautiful flower is truly fortunate. " +
        "They are held dear by whoever gave it. <toss [player] > will " +
        "enable you to give the rose to someone.\n");

    set_wilt_time(3000);
    set_flower_value(random(500) + 250);
    add_prop("_garden_flower", 1);
    add_prop(OBJ_I_VALUE, (random(500) + 250));
}
 
 
void init ()
{
   ::init ();
 
   add_action("toss_rose", "toss");
 
 }
 
 
 
int toss_rose(string str)
{
    object tgplayer;
    if(str == 0)
        {
            write("The syntax is: toss <player>\n");
            return 1;
         }
    tgplayer = find_player(str);
    if (tgplayer && tgplayer != environment())
        {
            tgplayer->catch_msg("You catch a red rose.\n");
            this_player()->catch_msg("You toss the rose to " +
                        QCTNAME(tgplayer) + " with a smile.\n");
            move (tgplayer, 1);
        }
    else
        {
            write("Who do you want to toss the rose to?\n");
        }
        return 1;
}
