#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
 
inherit ICEINROOM;

#define EMERALD_GEM clone_object("/d/Genesis/gems/obj/emerald")
#define RUBY_GEM clone_object("/d/Genesis/gems/obj/ruby")
#define SAPPHIRE_GEM clone_object("/d/Genesis/gems/obj/sapphire")
#define OPAL_GEM clone_object("/d/Genesis/gems/obj/opal")

object chest1,chest2,ioun1,ioun2,money1,money2,money3,
gem1,gem2,gem3,gem4,idscroll; 
int treasure = 1;

void
reset_icewall_room()
{
    if(treasure == 1)
    {
        if(!objectp(chest1))
        {
            chest1 = clone_object(OBJK + "trapped_chest");
            chest1->move(TO);
        }
        if(!objectp(chest2))
        {
            chest2 = clone_object(OBJK + "trapped_chest");
            chest2->move(TO);
        }
        if(!objectp(idscroll))
        if(random(3))
        {
            idscroll = clone_object(OBJK + "id_scroll");
            idscroll->move(chest1,1);
        }
        if(!objectp(ioun1))
        if(random(3))
        {
            ioun1 = clone_object(OBJK + "blue_ioun_stone");
            ioun1->move(chest1,1);
        }                        
        if(!objectp(ioun2))
        if(random(3))
        {
            ioun2 = clone_object(OBJK + "green_ioun_stone");
            ioun2->move(chest1,1);
        }                        
        if(!objectp(money1))
        {
            money1 = MONEY_MAKE_SC(random(1000));
            money1->move(chest2,1);
        }
        if(!objectp(money2))
        {
            money2 = MONEY_MAKE_GC(random(25));
            money2->move(chest2,1);
        }                       
        if(!objectp(money3))
        {
            money3 = MONEY_MAKE_PC(random(5));
            money3->move(chest2,1);
        }                       
        if(!objectp(gem1))
        if(random(3))
        {
            gem1 = EMERALD_GEM;
            gem1->move(chest2,1);
        }
        if(!objectp(gem2))
        if(random(3))
        {
            gem2 = RUBY_GEM;
            gem2->move(chest2,1);
        }
        if(!objectp(gem3))
        if(random(3))
        {
            gem3 = OPAL_GEM;
            gem3->move(chest2,1);
        }
        if(!objectp(gem4))
        {
            gem4 = SAPPHIRE_GEM;
            gem4->move(chest2,1);
        }
     
        treasure = 2;
    }
    else
        return;
}

void
create_icewall_room()
{

    set_short("Highlord's treasure chamber");
    set_long("@@long_descr");

   add_exit("bare_tunnel","east");

  add_item(({"books","book"}),"The books, written in ancient version " +
    "of the common language, deal with the Second Dragon War.\n");
  add_item(({"cabinet","weapons cabinet"}),"The weapons' cabinet is " +
    "quite empty.\n");
  add_item("rugs","Soft and tasteful rugs cover the stone floor, " +
    "giving this room a deceitful aura of comfort and friendship.\n");
  add_item(({"window","narrow window"}),"There are no windows here. " +
    "The room is illuminated by a soft magic glow.\n");
  add_item(({"furs","pillows","bed"}), "" +
    "The furs look soft and cozy, and the bed itself is more then " +
    "inviting. As you look at it, you cannot help but think how " +
    "comfortable and pillowy it would be... Especially with someone " +
    "to warm it for you.\n\nYou blink, sigh, and return to reality.\n");
  add_item(({"mirrors","walls"}),"Silver plated, crystal mirrors " +
    "span the walls. Worth a fortune, they present a most unusual " +
    "sight in a cold, frozen, and up to now, forsaken land of the " +
    "Icewall glacier.\n");
  add_item(({"manacles","chains"}),"Which ones? The wall, or the " +
    "bedpost irons?\n");
  add_item(({"wall manacles","wall irons","wall chains"}),"Your " +
    "eyes narrow as you appraise the manacles hanging from a thick " +
    "ring studded into the wall. The floor beneath the chains is the " +
    "only spot in the whole chamber showing cold, stone floor. Dark " +
    "stains mark the floor there, as well as the wall itself. " +
    "Obviously prisoners questioned here suffered not only from the " +
    "blows, but also from the knowledge that warmth and comfort " +
    "was just an armreach away.\n");
  add_item(({"bedpost manacles","bedpost irons","bedpost chains"}),"" +
    "The manackles " +
    "chained to the post at the head of the bed are smaller and of " +
    "finger quality. You are not sure if you wish to know what sort " +
    "of questioning has been practised there.\n");
  add_item(({"desk","huge desk","mahogeny desk"}),"The desk truly is " +
    "a piece of sturdy wood work. Scrolls and parchments cramped in " +
    "half-closed drawers show that its ownder, whoever else he " +
    "might be, is a scholar. Old, leather-bound books show years of " +
    "use, and seem even more fragile then the two grey skulls that " +
    "serve as gruesome paperweights.\n");
  add_item("map","The map looks new, and is carefully inked on the " +
    "thinnest of leathers by at least a master cartographer. " +
    "Displayed prominently upon it is the southern part of Ansalon. " +
    "Details such as the glacier covered mountains, and precisely " +
    "marked shoreline around the pre-cataclysm portcity of Tharsis " +
    "clearly indicates that it must have been sketched from air, or " +
    "completed with the help of obscure magic.\n");
  add_item(({"skulls","skull","grey skull","grey skulls"}),"The two " +
    "skulls are ancient and decaying. Human size, but with a delicate " +
    "jaw, they could come from a petite human female or an elf.\n");

  reset_room();
}


string
long_descr()

{ return ("" +
  "As you look around this spacious chamber, your battle instincts " +
  "scream in warning and your muscle tense for combat. Decorated with furs, " +
  "lined with crystal mirrors, carpeted with tasteful rugs, and " +
  "cozied by feathery pillows propped on a luxurious, canopied " +
  "bed fit for a king, the room looks like the bedchamber of a Queen... " +
  "At first glance, that is. Massive, iron-banded chests, " +
  "manackles chained to the wall and bedpost, weapon cabinet, " +
  "and most of all, a huge mahony desk on which two skulls " +
  "hold a gigantic map unrolled show that this is the home of a " +
  "general. One who delights in pain and pleasure, and one who " +
  "has the power to get exactly what he wants.\n");
}



int
lay(string str)
{
     if(str != "on bed")
        {
          notify_fail("Lay on what? The bed?\n");
          return 0;
        }

     write("With a sigh of pure pleasure, you collapse into the " +
      "fluffy furs, feeling like a Royalborn.\n");
     say(QCTNAME(TP) + ", with a sigh of pure pleasure, collapses " +
      "into the fluffy furs on the bed.\n");
     TP->add_fatigue(5);
     return 1;
} 
     
int
knock(string str)
{
    if(str == "on north wall")
      {
        write("You knock soundly on the north wall, but no hollow " +
         "sound accompanies your test.\n");        
        say(QCTNAME(TP) + " knocks soundly on the north wall, but " +
         "no hollow sound accompanies the test.\n");
        return 1;
      }

    if(str == "on south wall")
      {
       write("You knock soundly on the south wall, and faint hollow " +
         "sound rings out in response.\n");        
       say(QCTNAME(TP) + " knocks soundly on the south wall, and " +
         "faint hollow sound out in response.\n");
       tell_room(ROOMSK + "hall2", "A faint sound " +
         "of knocking resounds, as if someone was banging on the " +
         "north wall from the other side.\n");
       return 1;

      }

    notify_fail("Knock on which wall?\n");

    return 0;
}

void
init()
{
    ::init();

    add_action(knock, "knock");
    add_action(lay,"lay");
}
                  