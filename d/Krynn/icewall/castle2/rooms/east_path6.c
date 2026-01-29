#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

void
create_icewall_room()
{
    set_short("By the main gate");
    set_long("@@long_descr");

    add_exit("tunnel_gate","west","@@west",1,1);
    add_exit("east_path5","east","@@east",30);

    add_cmd_item("gate","open","@@noway");

    add_item(({"gate","massive gate"}),"Massive, ancient gate " +
     "blocks the way to the west. Darkened by age, covered " +
     "by ice, it appears as if it wasn't opened in at least a " +
     "decade. The feeling is reinforced by the fact that a " +
     "huge mound of snow rests against the gate.\n");
    add_item(({"huge mound","mound","mound of snow","huge mound of snow"}),
      "Aye, it is huge and it piles up against the castle's gate, " +
      "covering most of it.\n");
    add_item(({"steep path","path"}),"It cuts through the steep cliff, " +
     "working its way down from here. " +
     "Winding as it does, it prevents anyone from simply charging " +
     "the gate with a ram. It also gives the garrison ample time " +
     "to shoot anyone making its way up. The path appears unused, " +
     "and is covered high by white snow. It looks like the only " +
     "way out of here.\n");
    add_item(({"cliff","cliffs"}),"The snowy cliff makes the Icewall " +
     "castle easily defended from this flank.\n");
    add_item("mountains","High and heavy with snow, they appear devoid " +
     "of any living inhabitants. Most of them are covered with the great " +
     "Icewall glacier.\n");
    add_item(({"glacier","icewall glacier"}),"The glacier starts high in " +
     "mountains to the north, but over the ages the twinkling icy " +
     "carpet flowed south, into the flatlands.\n");
    add_item("castle","High above you to the west raises the " +
     "Icewall castle. Due to the sharp angle, you cannot see much " +
     "of it, just the tall, dark walls blocking the sky.\n");
    add_item("plains","Stretching as far as you can see, the plains " +
     "are white, and devoid of life.\n");
    add_item(({"forest","ice forest"}), "Below you to the southeast, a frozen " +
     "forest raises from the snow. A scary sight... Who knows what " +
     "dwells in it.\n");

    set_tell_time(800);

    add_tell("It is snowing hard... And white flakes begin to " +
     "cover you from head to toe.\n");
    add_tell("Wind picks up quite suddenly, scattering " +
     "snow and chilling you to the bone. You can " +
     "feel the first jabs of frostbite on your face. " +
     "This is definitely not a friendly land.\n");
    add_tell("You think you have just heard a strange shriek " +
     "carried here by the everpresent freezing wind.\n");
    add_tell("Snow whirls about you, creating myriad of patterns... " +
     "There is a strange beauty in them...\n\n\n" +
     "You shiver and slap your face. It must be the cold.\n");

}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string
long_descr()

{ return ("" +
  "You stand under the main gate of " +
  "the Icewall Castle. Here, the winding path cuts through the " +
  "snow-covered, rocky cliff, offering a way up the rocky slope. " +
  "However, it is for nought, as the gate is barred shut. The lord " +
  "of the castle apparently distrust any visitors. " +
  "Looking to the northeast and east, you can see snow fields stretch " +
  "far, empty and desolate. To the southeast, the frozen forest " +
  "raises like an undead being from the iced earth. Short of having " +
  "someone open the massive gate for you, there is no way to enter " +
  "the stronghold.\n");

}
int
east()
{
   write("Fighting your way through the mounds of snow, you slowly " +
    "make your way down the steep path. Just like the climb up, it's " +
    " an exhausting, and time consuming experience.\n");
   say(QCTNAME(TP) + " fights his way through the mounds on snow, " +
    "climbing down the steep path to the east. It takes his time.\n");
   return 0;
}

int
west()
{
  write("You have yet to learn the skill of passing THROUGH closed " +
   "gates.\n");
  say("Perhaps hoping for a local miracle, " + QTNAME(TP) + " attempts " +
   "to pass through the closed gate, but fails.\n");
  return 1;
}

string
noway()
{
  write("You would need a score of " +
     "minotaurs to accomplish that. The gate is frozen solid " +
     "and most likely barricaded. All you can do is bang on it.\n");
  say(QCTNAME(TP) + " moves as if to open the gate, but quickly " +
     "abandones the furtive idea.\n");
  return "";
}

int
bang(string str)
{
     if(str != "on gate")
       {
         notify_fail("Bang on what?\n");
         return 0;
       }

     write("You clench your hand in a fist and bang loudly on the " +
       "gate, hoping to be heard inside.\n");
     say(QCTNAME(TP) + " clenches his hand in a fist and bangs " +
       "loudly on the gate.\n");
     tell_room(ROOMSK + "tunnel_gate", "Someone bangs at the " +
       "gate, but the sound is faint and muted. You doubt it carries " +
       "further then this place.\n",TP);
     return 1;
}

void
init()
{
    ::init();

    add_action(bang, "bang");
}        

  