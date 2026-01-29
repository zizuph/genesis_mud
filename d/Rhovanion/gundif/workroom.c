inherit "/std/workroom";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
 
#define RHO_DIR "/d/Rhovanion/"
#define TPORT_ROOM "/d/Calia/glykron/palace/rooms/dark/black"
#define THIS_ROOM RHO_DIR+"gundif/workroom"
#define SITTING_IN_CHAIR "_sitting_in_my_chair_"
#define INVITED_TO_WORKROOM "_invited_to_gundifs_workroom_"
#define GUNDIF_ROOM_OWNER "_gundif_room_owner_"
/*     ._____________________________. */
/*     I ._____IUUUUUUUUI       ..   I */
/*     IoI  O==O               '  '  I */
/*     I I   \__\             '    ' I */
/*     I-'  .------------.     '..'  ( */
/*     )    I \    *~^.> I           ( */
/*     )    I        \/ 0I      ___  ( */
/*     )    I____________I     I d I I */
/*     I                       I___I I */
/*     I                             I */
/*     I                             I */
/*     I_________________.      \  I I */
/*     I                 I       =O= I */
/*     '-------------------=====-----' */
 
int inchair;
object sitting;
object room;
 
 
string query_inchair()
{
    if (sitting!=0)
         return QCTNAME(sitting)+"is sitting in it.\n";
 
    return "It is empty.\n";
}
 
 
void create_workroom()
{
    set_short("This is Gundif's workroom");
    set_long("This is a room of distorted proportions in something, "+
             "which seems to be ruins of a church or like building. "+
             "The room, while being quite comfortable sized and "+
             "homely, has walls which extend upwards till they "+
             "disappear in a strange, gray mist, which floats high "+
             "above your head, concealing the ceiling, if there is "+
             "any. There "+
             "is a huge, lit mantlepiece in the northern wall. "+
             "There is also a huge "+
             "writing desk in front of the mantlepiece, with a chair "+
             "behind it and a large shelf occupying the north-west "+
             "corner of the room, while the greater part of the "+
             "southern wall is hidden behind a bookcase. Looking "+
             "at the south-east corner, you notice an old, weather-"+
             "beaten skeleton, which stands with a heap of clothes "+
             "hanging on its outstretched hands. The north-east corner "+
             "is empty, only thing drawing your attention is a "+
             "large circle, drawn on the floor. You also notice a "+
             "small trapdoor leading down.\n");
 
    add_item(({"picture","pictures"}),"Several pictures hang on the "+
             "walls. Your attention is drawn by a painting of a "+
             "narrow and deep canyon, viewed from the edge, and "+
             "a picture of a dark and small bedroom, only feature "+
             "of it being a door glowing with greenish light.\n");
 
    add_item(({"wall","walls"}),"The walls are of grey, large stones, "+
            "and are bare, except for some pictures hanging on them.\n");
 
    add_item(({"desk","table"}),"This is a huge writing desk, made of "+
            "black oak and stained with various spots of unknown "+
            "origin. It is full of various chaotically laying "+
            "articles, leaving enough space for writing though. Among "+
            "the items, your eye is catched by a glass bottle with "+
            "something moving inside, a huge book bound in dark green "+
            "leather, a small, fine golden brooch featuring a pair of "+
            "twisted snakes, a blue steel dagger "+
            "as well as some blueprints.\n");
 
    add_item("skeleton","The skeleton would look as any other found "+
             "in a biology class, except that it seems to be "+
             "standing on its own legs. It has got a bunch of clothes "+
             "hanging on its outstretched hands, among which you "+
             "notice a deep-blue voluminous cloak and a black shirt. "+
             "There is also a hat put on the skeleton's skull, and "+
             "some perverted joker has put a lit cigar between "+
             "its teeth.\n\n"+
             "Suddenly, the skeleton sucks the cigar, making its end "+
             "glow brighter! He gives you a long look from "+
             "within his empty eyeholes, inside which you notice "+
             "dancing reflections of the firelight.\n");
 
    add_item("mantlepiece","The mantlepiece occupies the most part of "+
             "the northern wall. It is currently lit, warming and "+
             "lighting the room. The shadows are dancing on the shelf "+
             "and right behind the desk.\n");
 
    add_item("shelf","It is placed in the corner, "+
             "partially behind and partially beside a large chair. "+
             "The shelf is full of various items: vials, small and "+
             "large boxes, books and every else imaginable items.\n");
 
    add_item("circle","It is a circle, glowing faintly with a bluish "+
             "light, large enough for a man to stand in.\n");
 
    add_item("bookcase","The bookcase occupies the most part of the "+
             "southern wall. It is made of some deep red wood. The "+
             "upper end of the bookcase is lost in the mist.\n");
 
    add_item("mist","The mist hangs some good ten metres above your "+
             "head, creating an impression of something moving inside "+
             "it.\n");
 
    add_item("trapdoor","The trapdoor leads down. It is open and you "+
             "glimpse a view of some big crates and boxes down "+
             "there.\n");
 
    add_item("chair","The large armchair is made of some unknown "+
             "black wood, seat and back being of deep blue leather." +
             query_inchair());
 
    inchair=0;
    sitting=0;
 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
 
    add_exit(RHO_DIR+"gundif/private/room1","down");
 
}
 
 
int sit_in_chair()
{
 
    if (inchair)
    {
         NF(QCTNAME(sitting)+" is already sitting in it!\n");
         return 0;
    }
    TP->catch_msg("You sit down on the big old chair, and make "+
                  "yourself feel comfortable.\n");
    say(QCTNAME(TP)+" sits in the old armchair.\n");
    TP->add_prop(SITTING_IN_CHAIR,1);
    TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in an old armchair");
    sitting=TP;
    inchair=1;
 
    return 1;
}
 
int stand_up()
{
    if (TP->query_prop(SITTING_IN_CHAIR)==1)
    {
         TP->catch_msg("With a sigh you force yourself to stand "+
                       "up from the old chair.\n");
         sitting=0;
         say(QCTNAME(TP)+" emerges from the old armchair with a "+
         "sigh.\n");
 
         TP->remove_prop(SITTING_IN_CHAIR);
         TP->remove_prop(LIVE_S_EXTRA_SHORT);
         inchair=0;
 
         return 1;
 
    }
    NF("You are not sitting!\n");
    return 0;
}
 
leave_inv(object ob,object place)
{
    if (ob->query_prop(SITTING_IN_CHAIR)==1)
    {
         ob->catch_msg("Stand up from the chair first, perhaps?\n");
         ob->move(THIS_ROOM);
    }
    else if (ob->query_prop(INVITED_TO_WORKROOM)!=0)
                  ob->remove_prop(INVITED_TO_WORKROOM);
}
 
 
int teleport(string arg)
{
    if (arg=="at picture")
    {
     if (TP->query_prop(GUNDIF_ROOM_OWNER)==1)
     {
         TP->catch_msg("You take a deeper look at the picture of "+
         "the castle, and somehow it absorbs all your attention "+
         "drawing you in...\n");
         say(QCTNAME(TP)+" gazes at the painting of the castle "+
         "and seems to have lost his sense of reality... "+
         "Obviously, the picture has absorbed all his attention. "+
         "Slowly "+HIS(TP)+" figure begins to fade, till it "+
         "becomes a pitch black contour, which suddenly vanishes "+
         "causing a rush of wind as the air fills the empty place.\n");
 
         TP->move_living("M",TPORT_ROOM,1);
 
         return 1;
      }
      NF("You gaze at the picture... but nothing happens.\n");
      return 0;
    }
    NF("Gaze at what?\n");
    return 0;
}
 
int trans_man(string arg)
{
    object ob,roomobj;
    if (TP->query_prop(GUNDIF_ROOM_OWNER)==1)
    {
     if (arg)
     {
      ob=find_living(LOW(arg));
      if (ob)
      {
       tell_room(this_room(),QCTNAME(TP)+" points at the circle "+
                       "drawn on the "+
                       "floor and snaps his fingers.\n",TP);
       TP->catch_msg("You point at the circle, and summon "+QCTNAME(ob)+
             ".\n");
       ob->catch_msg("Suddenly, the world shatters to the pieces!"+
                  "There is a rumbling sound, like a slow thunder "+
                  "and with a whoosh the world becomes whole again.\n");
       ob->move_living("M",THIS_ROOM,1);
       tell_room(this_room(),QCTNAME(ob)+" appears in the circle.\n",ob);
 
 
       room=ob->query_prop(LIVE_O_LAST_ROOM);
       ob->add_prop(INVITED_TO_WORKROOM,room);
       room=0;
 
       TP->catch_msg("Will be sent back to: "+
       file_name(ob->query_prop(INVITED_TO_WORKROOM))+".\n");
 
       tell_room(room,QCTNAME(ob)+" is suddenly engulfed in a "+
       "tingling swirlpool of grey clouds. As the clouds fade away "+
       "the only thing remaining is "+QCTNAME(ob)+" body's contour, "+
       "which glows red for a moment, and then crumbles to dust.\n");
 
       return 1;
       }
      NF("Summon whom to your workroom?\n");
      return 0;
      }
     NF("Only the owner of this room can summon here.\n");
     return 0;
    }
}
 
int go_back()
{
    if (TP->query_prop(INVITED_TO_WORKROOM)!=0)
    {
         TP->catch_msg("As you enter the door, you feel as "+
         "if being pulled inside out...\nThen inside in again.\n");
         say(QCTNAME(TP)+" leaves back.\n");
         room=TP->query_prop(INVITED_TO_WORKROOM);
 
         TP->remove_prop(INVITED_TO_WORKROOM);
 
         TP->move_living("M",file_name(room),1);
         tell_room(room,"Suddenly, a door appears in thin air. "+
                   "It swings open, and "+QCTNAME(TP)+" steps "+
                   "out of it.\n",TP);
         room=0;
         return 1;
    }
    NF("Since you haven't arrived by an invitation, find a way "+
        "out yourself!\n");
    return 0;
}
 
void init()
{
    ::init();
    add_action("sit_in_chair","sit");
    add_action("trans_man","summon");
    add_action("stand_up","stand");
    add_action("go_back","back");
    add_action("teleport","gaze");
}
