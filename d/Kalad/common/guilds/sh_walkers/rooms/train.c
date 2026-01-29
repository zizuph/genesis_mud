inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#define CLOSED 0

object ob;
void reset_room();

int closed;
object meditate;
create_room() 
{
   ::create_room();
   closed = CLOSED;
   INSIDE;
   set_short("The Shadow Walkers of Kabal training room");
   set_long("You are in a dark, spacious room. The walls are bare, "+
   "and the ceiling reaches up high. In the room, you see a dummy "+
   "dressed up like a noble with many bells on it. You see "+
   "a dirty sack, rack, and some buckets laying about.\n");
   add_item("buckets","Iron pails filled with water. In one, "+
   "you see some rags. In another, you see black dust.\n");
   add_item("rack","A rack filled with bottles.\n");
   add_item("dummy","A human dummy with many pockets with a number of "+
   "bells on it.\n");
   add_item(({"sack","dirty sack"}),"You see a sack full of long, "+
   "thing wires.\n");

    add_item(({"students","novices"}),"You see a few students "+
    "here learning from the master trainerer.\n");
   add_item("plaque","Several words have been written upon it.\n");

   add_cmd_item("plaque","read","Here you may train in the following skills:\n"+
      "Sneak ----------- Superiour Accolyte\n"+
      "Hide  ----------- Superiour Journeyman\n"+
      "Find/Remove Traps Superiour Journeyman\n"+
      "Pick Pocket ----- Superiour Journeyman\n"+
      "Alchemy --------- Superiour Layman\n"+
      "Awareness ------- Superiour Professional\n"+
      "Appraise Value -- Confident Veteran\n"+
    "Herbalism -- Superiour Layman\n"+
      "Weapon skills are to the east.\n");

   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   
add_exit("/d/Kalad/common/guilds/shadow_walkers/t11","southeast","@@bck@@",-1,1);
   add_exit("/d/Kalad/common/guilds/shadow_walkers/train2","east",0,-1,1);
   create_guild_support();
   create_skill_raise();
   set_up_skills();
    clone_object("/d/Kalad/common/guilds/shadow_walkers/basin")->move(TO);
   reset_room();
   clone_object("/d/Kalad/common/guilds/shadow_walkers/book")->move(TO);
}

int
bck()
{
    object book;
    if(book = present("book",TP))
    {
        if(MASTER_OB(book) == "/d/Kalad/common/guilds/shadow_walkers/book")
        {
            write("You can't leave this room with the "+book->short()+".\n");
            return 1;
        }
    }
    return 0;
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object("/d/Kalad/common/guilds/shadow_walkers/trainer1");
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Sarr.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!query_ip_number(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("\n\nWARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/guilds/shadow_walkers/t11");
   }
}
init() {
   init_guild_support();
   init_skill_raise();
    AA(do_get,get);
   ::init();
}
    
int
do_get(string str)
{
    NF("Get what from where?\n");
    if(str == "wire from sack")
    {
    clone_object("/d/Kalad/common/guilds/shadow_walkers/wire")->move(TP);
    write("You get a wire from the sack.\n");
    say(QCTNAME(TP)+" gets a wire.\n");
    return 1;
    }
    if(str == "rag from bucket")
    {
    clone_object("/d/Kalad/common/guilds/shadow_walkers/rag")->move(TP);
    write("You get a rag from the bucket.\n");
    say(QCTNAME(TP)+" gets a rag.\n");
    return 1;
    }
    if(str == "dust from bucket")
    {
    clone_object("/d/Kalad/common/guilds/shadow_walkers/dust")->move(TP);
    write("You get some dust from the bucket.\n");
    say(QCTNAME(TP)+" gets some dust.\n");
    return 1;
    }
    if(str == "bottle from rack")
    {
    /* removed until ready.
    clone_object("/d/Kalad/common/guilds/shadow_walkers/bottle")->move(TP);
    write("You get a bottle from the rack.\n");
    say(QCTNAME(TP)+" gets a bottle.\n");
    */
write("There are no bottles in the rack to take.\n");
    return 1;
    }
    return 0;
}

close_guild() {
   if (closed) {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}

query_closed() {return closed;}
set_up_skills() {
   sk_add_train(SS_HIDE, train_text(SS_HIDE), 0,0,50);
   sk_add_train(SS_SNEAK, train_text(SS_SNEAK), 0,0,40);
   sk_add_train(SS_ALCHEMY, train_text(SS_ALCHEMY), 0,0,30);
   sk_add_train(SS_PICK_POCKET, train_text(SS_PICK_POCKET), 0,0,50);
   sk_add_train(SS_FR_TRAP, train_text(SS_FR_TRAP), 0,0,50);
   sk_add_train(SS_AWARENESS, train_text(SS_AWARENESS), 0,0,70);
   sk_add_train(SS_APPR_VAL, train_text(SS_APPR_VAL), 0,0,75);
    sk_add_train(SS_HERBALISM,train_text(SS_HERBALISM),0,0,30);
}

train_text(skill) {
   string what;
   switch(skill) {
      case SS_FR_TRAP:
      what="work with traps better";
      break;
      case SS_ALCHEMY:
      what="use the arts of alchemy better";
      break;
      case SS_WEP_KNIFE:
      what="use a dagger more effectivly";
      break;
      case SS_PICK_POCKET:
      what="steal from others better";
      break;
    case SS_HERBALISM:
    what="find herbs better";
    break;
      case SS_SNEAK:
      what="move around more covertly";
      break;
      case SS_HIDE:
      what="conceal things better";
      break;
      case SS_AWARENESS:
      what="be more aware of your surroundings better";
      break;
      case SS_APPR_VAL:
      what="estimate the values of objects more accuratly";
      break;
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}

