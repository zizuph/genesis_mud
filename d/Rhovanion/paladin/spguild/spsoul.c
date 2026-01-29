 
inherit "/cmd/std/command_driver";
#include <spguild.h>
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
 
string
get_soul_id()
{
    return "spsoul";
}
 
int
query_cmd_soul()
{
    return 1;
}
 
mapping
query_cmdlist()
{
    return( [ "debugspider" : "debug_spider",
              "whistle" : "whistle_for_spider",
              "return" : "return_spider",
              "dismount" : "dismount_spider",
              "mount" : "mount_spider",
              "pack" : "pack_object",
              "unpack" : "unpack_object",
              "packinv" : "pack_inventory"
            ]);
}
 
object subloc;
object shield;
object shadow;
 
int
debug_spider(string arg)
{
    TP->remove_prop(SPIDER);
    return 1;
}
 
int
whistle_for_spider(string arg)
{
    if (arg!="for spider") return 0;
    setuid();
    seteuid(getuid());
    if (TP->query_prop(SPIDER))
      {
        write("You already have a spider!\n");
        return 1;
      }
    TP->add_prop(MOUNTED,1);
    subloc=clone_object(GUILDDIR+"subl_spider.c");
    subloc->install(TP);
    TP->add_prop(SPIDER,clone_object(GUILDDIR+"gspider.c"));
    TP->query_prop(SPIDER)->move(GUILDDIR+"gstables.c");
    write("You call your spider and mount it.\n");
    shield=clone_object(GUILDDIR+"gshield.c");
    shield->move(TP);
    shield->power(TP->query_skill(SPIDER_RIDE_SKILL)-50);
    TP->wear_arm(shield);
    shadow=clone_object(GUILDDIR+"spshadow.c");
    shadow->install(TP);
    return 1;
}
 
int
return_spider(string arg)
{
    NF("Return what?\n");
    if (arg!="spider") return 0;
    NF("You must have a spider in order to return it.\n");
    if (!(subloc)) return 0;
    subloc->remove_me();
    subloc=0;
    write("You let your spider to return home.\n");
    TP->query_prop(SPIDER)->remove_object();
    TP->remove_prop(SPIDER);
    shield->remove_object();
    shadow->remove_shadow();
    return 1;
}
 
int dismount_spider(string arg)
{
    NF("Dismount what?\n");
    if (arg!="spider") return 0;
    if (!TP->query_prop(SPIDER))
      {
        write("You don't have a spider yet!\n");
        return 1;
      }
    if (TP->query_prop(MOUNTED))
      {
        subloc->remove_me();
        subloc=0;
        TP->remove_prop(MOUNTED);
        TP->query_prop(SPIDER)->move(ENV(TP));
        write("You dismount your spider.\n");
        say(QCTNAME(TP)+" dismounts his huge black spider.\n");
        shield->remove_object();
      }
    else
      write("You are not riding your spider!\n");
    return 1;
}
 
int mount_spider(string arg)
{
    NF("Mount what?\n");
    if (arg!="spider") return 0;
    if (!TP->query_prop(SPIDER))
      {
        write("You don't have a spider yet!\n");
        return 1;
      }
    if (!(TP->query_prop(MOUNTED)))
        if (ENV(TP)==ENV(TP->query_prop(SPIDER)))
          {
            TP->query_prop(SPIDER)->move(GUILDDIR+"gstables.c");
            subloc=clone_object(GUILDDIR+"subl_spider.c");
            subloc->install(TP);
            TP->add_prop(MOUNTED,1);
            write("You mount your spider.\n");
            say(QCTNAME(TP)+" mounts his huge black spider.\n");
            shield=clone_object(GUILDDIR+"gshield.c");
            shield->power(TP->query_skill(SPIDER_RIDE_SKILL)-50);
            shield->move(TP);
            TP->wear_arm(shield);
          }
        else
            write("Your spider isn't here to mount it!\n");
    else
        write("You have already mounted your spider!\n");
    return 1;
}
 
int
pack_object(string arg)
{
    object *list;
    mixed *what;
    int response;
 
    if (!TP->query_prop(SPIDER))
      {
        NF("Perhaps you should call for your spider first?\n");
        return 0;
      }
if ((ENV(TP)!=ENV(TP->query_prop(SPIDER)))&&(!(TP->query_prop(MOUNTED))))
      {
        NF("Your spider isn't here to pack anything!\n");
        return 0;
      }
    NF("Pack what?\n");
    list=all_inventory(TP);
    if (!(parse_command(arg,list,"%i",what))) return 0;
    if (what[0]=0||what[0]>1)
      {
        NF("Please be specific what do you want to pack?\n");
        return 0;
      }
    if (what[1]->query_prop(HEAP_I_IS))
      {
        NF("Sorry you cannot pack "+arg+" on your spider.\n");
        return 0;
      }
    response=what[1]->move(TP->query_prop(SPIDER));
    if (!response)
      {
        TP->catch_msg("You pack "+what[1]->query_short()+
                      " on your spider.\n");
        say(QCTNAME(TP)+" packs "+what[1]->query_short()+
                      " on his spider.\n");
        return 1;
      }
    if (response==1)
      {
        NF("Your spider cannot carry so much weight!\n");
        return 0;
      }
    if (response==8)
      {
        NF("It is too large for your spider!\n");
        return 0;
      }
    NF("This item cannot be packed!\n");
    return 0;
}
 
int
unpack_object(string arg)
{
    object *list;
    mixed *what;
    int response;
 
    if (!TP->query_prop(SPIDER))
      {
        NF("Perhaps you should call your spider first?\n");
        return 0;
      }
if ((ENV(TP)!=ENV(TP->query_prop(SPIDER)))&&(!(TP->query_prop(MOUNTED))))
      {
        NF("Your spider isn't here to unpack anything!\n");
        return 0;
      }
    NF("Unpack what?\n");
    list=all_inventory(TP->query_prop(SPIDER));
    if (!(parse_command(arg,list,"%i",what))) return 0;
    if (what[0]=0||what[0]>1)
      {
        NF("Please be specific what do you want to unpack?\n");
        return 0;
      }
    response=what[1]->move(TP);
    if (!response)
      {
        TP->catch_msg("You unpack "+what[1]->query_short()+
                      " from your spider.\n");
        say(QCTNAME(TP)+" unpacks "+what[1]->query_short()+
                      " from his spider.\n");
        return 1;
      }
    if (response==1)
      {
        NF("You cannot carry so much weight!\n");
        return 0;
      }
    if (response==8)
      {
        NF("It is too large for you to carry!\n");
        return 0;
      }
    NF("This item cannot be unpacked!\n");
    return 0;
}
 
int pack_inventory()
{
    object *list;
    int i;
 
    if (!TP->query_prop(SPIDER))
      {
        NF("Maybe you at least should have your spider?!\n");
        return 0;
      }
if ((ENV(TP->query_prop(SPIDER))!=ENV(TP))&&(!(TP->query_prop(MOUNTED))))
      {
        NF("Your spider isn't here so you cannot see what is"+
           " it carrying.\n");
        return 0;
      }
    list=all_inventory(TP->query_prop(SPIDER));
    if (!sizeof(list))
      {
        TP->catch_msg("Hmm... Your spider doesn't seem to"+
            " carry anything.\n");
        return 1;
      }
    TP->catch_msg("  ******************************"+
                  "*******************************************\n");
    TP->catch_msg("Your spider is carrying:\n");
    for (i=0;i<sizeof(list);i++)
        TP->catch_msg(list[i]->query_short()+"\n");
    TP->catch_msg("  ******************************"+
                  "*******************************************\n");
    return 1;
}
