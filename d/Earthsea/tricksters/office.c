#include <macros.h>

#include "defs.h"

inherit TRICKSTER_STD_ROOM;

string confirm_ban="";

void create_room()
{
 set_short("Tricksters council office");
 set_long(BS("You find yourself in the middle of big room. In the "+
   "corner you see statue. Big table in the middle of the room , this "+
   "is where Jamadar of Jamadars works , near it few smaller tables "+
   "for Jamadars. Near the wall you see shelf with books , they look "+
   "important , maybe you should take a closer look. Down on the floor "+
   "you see carpets. In the middle of the room there is a board for "+
   "Council matter discussions. Northeast arch leads back to hallway , "+
   "you see a mosaic above it.\n"));

 add_item("statue","This is statue of Narayan Singh , legendary "+
   "saint of Tricksters. He was the most beloved servant of Kina "+
   "and founder of Tricksters guild.\n");
 add_item("table","You see several tables , be more specific\n");
 add_item("big table","Table of red wood , looks very sturdy and "+
   "solid , this is where Jamadar of Jamadars does his work. You "+
   "see couple of drawers , with big locks on them. Several chairs "+
   "spread around the table.\n");
 add_item(({"chair","chairs"}),"Chairs are spread around several "+
   "tables. They look comfortable and nice.\n");
 add_item("smaller tables","Smaller tables look humbler then big "+
   "one , though they still look very rich and nicely decorated. "+
   "These are work places of Jamadars , guild leader's assistants. "+
   "Couple of chairs are spread around the tables.\n");
 add_item("shelf","Shelf filled with all kind of books. Books look "+
   "important , so you'd better come closer and examine them.\n");
 add_item("books","@@exa_books");
 add_item(({"carpets","carpet"}),"Carptes cover the floor completely. "+
   "They look very rich , well-decorated and soft on touch.\n");
 add_item("mosaic","@@exa_mosiac");

 clone_object(TRICKSTERS+"obj/council_board")->move(TO);

 add_exit(TRICKSTERS+"hall","northeast");
}

string exa_mosiac()
{
 write("You see picture of Kina , Goddess of Mischief. She looks "+
   "enormous , higher then trees. She has four pair of hands and "+
   "three pair of breasts , on the necklace around her neck you "+
   "see children sculls , while on belt around her hips you see men "+
   "falloses.\n");
 say(QCTNAME(TP)+" studies the mosaic\n");
 TP->command("gasp");
 return "";
}

string exa_books()
{
 return "|----------------------------------------------|\n"+
        "|     Council members can do the following     |\n"+
        "|----------------------------------------------|\n"+
        "|                                              |\n"+
        "|  o list members - List all tricksters        |\n"+
        "|  o list council - List councilmembers        |\n"+
        "|  o list restrict - List restricted members   |\n"+
        "|  o list punish - List punished members       |\n"+
        "|  o list ban - List baned players             |\n"+
        "|  o list apply - List current applicants      |\n"+
        "|  o list appeal - List of current appeals     |\n"+
        "|  o list approved - List approved applicants  |\n"+
        "|  o list rejected - List rejected applicants  |\n"+
        "|  o list maxjamadar - See maximum number of   |\n"+
        "|      Jamadars allowed                        |\n"+
        "|  o list promotion plan - See promotions or   |\n"+
        "|      demotions for players who still havn't  |\n"+
        "|      logged in                               |\n"+
        "|                                              |\n"+
        "|  o study <name> - Study the application or   |\n"+
        "|      appeal and all the responds to it       |\n"+
        "|  o respond <name> - Respond to application   |\n"+
        "|      or appeal                               |\n"+
        "|  o approve <name> - Approve applicant        |\n"+
        "|  o reject <name> - Reject applicant          |\n"+
        "|                                              |\n"+
        "|  o promote <name> - Promote Trickster        |\n"+
        "|  o demote <name> - Demote Trickster          |\n"+
        "|  o promote cancel <name> - Cancel planned    |\n"+
        "|      promotion/demotion                      |\n"+
        "|                                              |\n"+
        "|  o restrict <name> - Restrict from training  |\n"+
        "|  o restrict remove <name> - Remove restrict  |\n"+
        "|                                              |\n"+
        "|     Jamadar of Jamadars only:                |\n"+
        "|  o discard respond <name> - Remove the       |\n"+
        "|      latest respond to <name>                |\n"+
        "|  o revert <name> - Revert Council decision   |\n"+
        "|      on rejecting or approving applicant     |\n"+
        "|  o dismiss <name> - Dismiss application      |\n"+
        "|      or appeal                               |\n"+
        "|  o block apply - Close guild for applicants  |\n"+
        "|  o block remove - Allow applications         |\n"+
        "|  o accept <name> - Accept into Jamadars      |\n"+
        "|  o deny <name> - Deny from Jamadars          |\n"+
        "|  o ban <name> - Banish from guild            |\n"+
        "|      Baned player can't apply to guild again |\n"+
        "|  o ban lift <name>  - Lift ban               |\n"+
        "|  o punish <name> - Disable all abilities     |\n"+
        "|  o punish remove <name> - Remove punishment  |\n"+
        "|  o relinquish leadership to <name> -         |\n"+
        "|      Give up leadership to Jamadar           |\n"+
        "|  o declare <msg> - Tell msg to all           |\n"+
        "|      Tricksters online                       |\n"+
        "|                                              |\n"+
        "|     Guild Master only:                       |\n"+
        "|  o maxjamadar <num> - Set maximum limit of   |\n"+
        "|      Jamadars allowed.                       |\n"+
        "|    In case Guildleader thinks that he needs  |\n"+
        "|      more/less Jamadar positions , he/she    |\n"+
        "|      shell mail GuildMaster immediately and  |\n"+
        "|      explain his/her considerations.         |\n"+
        "|                                              |\n"+
        "|----------------------------------------------|\n";
}

void init()
{
 ::init();
 add_action("accept","accept");
 add_action("deny","deny");
 add_action("list","list");
 add_action("restrict","restrict");
 add_action("relinquish","relinquish");
 add_action("maxjamadar","maxjamadar");
 add_action("ban","ban");
 add_action("study","study");
 add_action("respond","respond");
 add_action("reject","reject");
 add_action("approve","approve");
 add_action("revert","revert");
 add_action("promote","promote");
 add_action("demote","demote");
 add_action("punish","punish");
 add_action("dismiss","dismiss");
 add_action("block","block");
 add_action("declare","declare");
 add_action("discard","discard");
}

int accept(string name)
{
 NF("Accept who?\n");
 if(!name) return 0;

 (SERVER)->accept_jamadar(name);
 return 1;
}

int deny(string name)
{
 NF("Deny who?\n");
 if(!name) return 0;

 (SERVER)->deny_jamadar(name);
 return 1;
}

int list(string what)
{
 NF("List what?\n");
 if(!what) return 0;

 if(what=="members")
  {
   write("Current members of Tricksters:\n");
   write((SERVER)->members_string()+"\n");
   return 1;
  }

 if(what=="council")
  {
   write("Following Tricksters are CouncilMembers:\n");
   write("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
   write(BS(" - GuildMaster : "+(SERVER)->query_guildmaster()+"\n"));
   write(BS(" - Jamadar of Jamadars : "+(SERVER)->get_leader()+"\n"));
   write(BS(" - Jamadars : "+(SERVER)->jamadars_string()+"\n\n"));
   write("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
   return 1;
  }

 if(what=="restrict")
  {
   write(sprintf("  %-12s %s\n","Name","Restricted by"));
   write("===========================================\n");
   write((SERVER)->restrict_string());
   write("===========================================\n");
   return 1;
  }

 if(what=="maxjamadar")
  {
   write(sprintf("Maximum number of Jamadars allowed is %d\n",
     (SERVER)->query_max_jamadar()));
   return 1;
  }

 if(what=="apply")
  {
   write("List of current applicants:\n");
   write((SERVER)->apply_string()+"\n");
   return 1;
  }

 if(what=="rejected")
  {
   write((SERVER)->rejected_string());
   return 1;
  }

 if(what=="approved")
  {
   write((SERVER)->approved_string());
   return 1;
  }

 if(what=="promotion plan")
  {
   write((SERVER)->promotion_plan_string());
   return 1;
  }

 if(what=="punish")
  {
   write((SERVER)->punished_string());
   return 1;
  }

 if(what=="ban")
  {
   write((SERVER)->baned_string());
   return 1;
  }

 if(what=="appeal")
  {
   write((SERVER)->appeal_string());
   return 1;
  }

 return 0;
}

int restrict(string what)
{
 int res;
 string name;

 NF("Restrict what?\n");
 if(!what) return 0;

 res=sscanf(what,"remove %s",name);
 if(res>0)
  {
   (SERVER)->unrestrict_member(name);
   return 1;
  }

 name=what;
 (SERVER)->restrict_member(name);
 return 1;
}

int relinquish(string what)
{
 int res;
 string name;

 NF("Relinquish leadership to whom?\n");
 if(!what) return 0;
 res=sscanf(what,"leadership to %s",name);
 if(!res) return 0;

 (SERVER)->exchange_leader(name);
 return 1;
}

int maxjamadar(string nm)
{
 int num;

 NF("How many max Jamadars?\n");
 if(!nm) return 0;

 NF("Please give number greater then zero.\n");
 if(!sscanf(nm,"%d",num)) return 0;
 if(num<1) return 0;
 
 (SERVER)->set_max_jamadar(num);
 return 1;
}

int ban(string who)
{
 string name;

 NF("Banish whom?\n");
 if(!who) return 0;

 if(sscanf(who,"lift %s",name))
  {
   (SERVER)->remove_baned(name);
   return 1;
  }

 (SERVER)->add_baned(who);
 return 1;
}

int study(int who)
{
 NF("Study whose application?\n");
 if(!who) return 0;

 MORE((SERVER)->get_info(who),0,0);
 return 1;
}

int respond(string who)
{
 NF("Respond to whose application?\n");
 if(!who) return 0;

 (SERVER)->respond_apply(who);
 return 1;
}

int reject(string who)
{
 NF("Reject who?\n");
 if(!who) return 0;

 (SERVER)->reject_applicant(who);
 return 1;
}

int approve(string who)
{
 NF("Approve who?\n");
 if(!who) return 0;

 (SERVER)->approve_applicant(who);
 return 1;
}

int revert(string who)
{
 NF("Revert whose application?\n");
 if(!who) return 0;

 (SERVER)->revert_apply(who);
 return 1;
}

int promote(string who)
{
 int res,lv;
 string name;

 NF("Promote who?\n");
 if (!who) return 0;

 res=sscanf(who,"cancel %s",name);
 if(res)
  {
   (SERVER)->cancel_promotion(name);
   return 1;
  }

 res=sscanf(who,"%s %d",name,lv);
 if(!res) (SERVER)->promote(who,1);
 else 
  {
   NF("Promote how many levels?\n");
   if(lv<=0) return 0;
   (SERVER)->promote(name,lv);
  }
 return 1;
}

int demote(string who)
{
 int res,lv;
 string name;

 NF("Demote who?\n");
 if (!who) return 0;

 res=sscanf(who,"%s %d",name,lv);
 if(!res) (SERVER)->demote(who,1);
 else 
  {
   NF("Demote how many levels?\n");
   if(lv<=0) return 0;
   (SERVER)->demote(name,lv);
  }
 return 1;
}

int punish(string who)
{
 string name;

 NF("Punish who?\n");
 if(!who) return 0;

 if(sscanf(who,"remove %s",name))
  {
   (SERVER)->unpunish_member(name);
   return 1;
  }

 (SERVER)->punish_member(who);
 return 1;
}

int dismiss(string who)
{
 NF("Dismiss what?\n");
 if(!who) return 0;

 (SERVER)->dismiss(who);
 return 1;
}

int block(string what)
{
 NF("Block what?\n");
 if(!what) return 0;
 if(what!="apply" && what!="remove") return 0;

 if(what=="apply") (SERVER)->block_apply();
   else (SERVER)->block_remove();
 return 1;
}

int declare(string msg)
{
 NF("Declare what?\n");
 if(!msg) return 0;

 NF("You have no authority to do that.\n");
 if(!(SERVER)->query_leader(TP->query_name())) return 0;

 (SERVER)->tell_all(msg);
 return 1;
}

int discard(string what)
{
 string nm;

 NF("Discard respond maybe?\n");
 if(!what) return 0;

 NF("Discard respond to whos apply?\n");
 if(!sscanf(what,"respond %s",nm)) return 0;

 (SERVER)->discard_respond(nm);
 return 1;
}

