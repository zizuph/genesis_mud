inherit "/std/armour.c";
/* Orginal code by Terel members
 * smove was coded by Ged
 * cdone, cdonelog, cnote, cnotes added by Glindor
 * fixlog added by Glindor
 * cte - roke talkline emote by Gresolle
 * cp - roke people by Gresolle
 * zap by Gresolle
 * set_stat by Gresolle
 */

#define CHECK_SO_WIZ    if (WIZ_CHECK < WIZ_APPRENTICE) return 0; \
                        if (this_interactive() != this_player()) return 0
#define SPECIAL_WIZ ({"Ged","Gresolle","Glindor"})

#include "/d/Cirath/common/defs.h"
#define MORE_OBJ "/std/board/board_more"
#define SECRET "/d/Roke/varl/atuan/cape/guild/councilrm"

inherit "/cmd/std/command_driver";
inherit "/lib/time";
#include "/cmd/std/tracer_tool_base.c";
#include <filepath.h>
#include <language.h>
#include <std.h>
#include <ss_types.h>
#include <composite.h>
#include <wa_types.h>
#define DOMAIN "Cirath"
#define NOTELOG "/d/Cirath/log/notes"
#define DONELOG "/d/Cirath/log/done"


#define HELP \
"The following commands are available through this fur:\n" +\
"help fur ---------------------> Gets this message.\n" +\
"ct <message>  ----------------> Sends messages on the "+DOMAIN+" talkline.\n" +\
"cte <message> ----------------> Sends an emote on the "+DOMAIN+" line.\n" +\
"cirp -------------------------> Displays every "+DOMAIN+" wizard and\n" +\
"                                player in the area.\n" +\
"zap --------------------------> A quick way to kill and npc.\n" +\
"set_stat ---------------------> Sets all your stats at a specific\n" +\
"                                for a short time.\n" +\
"smove <target> ---------------> Moves you silently to a target.\n" +\
"cnote ------------------------> Make a note.\n" +\
"cdone ------------------------> Show what you have finished.\n" +\
"cnotes -----------------------> List all notes made.\n" +\
"cdonelog ---------------------> List everything noted as done.\n" +\
"fixlog -----------------------> Fix a log.\n" +\
"cglance <target> -------------> See the room a player is in.\n" +\
"cdir <target> ----------------> Change directory to the target's room.\n"


string TPN; /* This Player Name */
string TDM; /* This Players Domain */
int busy = 0;


query_auto_load() {
  string name;
  int i;

  sscanf(file_name(this_object()),"%s#%d", name, i);
  return name;
}


int
stealthmove(string dest)
{
    object          ob,
                    wlx,
                    wly,
                    slx,
                    sly;
    string name;

    CHECK_SO_WIZ;

    if (!dest)
    {
        notify_fail("Goto where ?\n");
        return 0;
    }

    ob = find_living(dest);
    if ((ob) && (environment(ob)))
    {
        ob = environment(ob);

        this_interactive()->move(ob);
        return 1;
    }

    if (sscanf(dest, "x%d.%dy%d.%d", wlx, slx, wly, sly) == 4)
    {
        dest = (string)"/std/room"->map_file(dest);
    }
    name = dest;
    dest = FTPATH((string)this_interactive()->query_path(), dest);

    if (!strlen(dest) || catch(this_interactive()->move(dest)))
    {
        notify_fail("Invalid monster name or file name: " + dest + "\n");
        return 0;
    }
    return 1;
}

create_armour() {
  set_name("fur");
  add_name("cirathfur");
  set_short("large fur");
  set_long("A fake fur.\n");
  add_prop(OBJ_M_NO_DROP,1);
  set_default_armour(40, A_ROBE, ({-4,4,0}), 0);
  add_prop(OBJ_I_WEIGHT,0);
  add_prop(OBJ_I_VOLUME,0);

  TPN = capitalize(this_player()->query_real_name());

if("/secure/master"->query_wiz_dom(TPN)!="Cirath" && member_array(TPN,SPECIAL_WIZ) == -1)
      call_out("remove_object",1);
  else
      if(TPN == "Ged" || TPN == "Glindor")
      {
     call_out("ct",1,"Proctor "+TP->query_name()+" has ventured into "+
              "the wastes.\n");
      }
      else
      {
          if(TPN == "Vladimir" )
          {
     call_out("ct",1,"Lord "+TP->query_name()+" Tepes has ventured into "+
              "the wastes.\n");
          }
          else
          {
     call_out("ct",1,TP->query_name()+" has ventured into the wastes.\n");
          }
      }
}
remove_object()
{
  ct(capitalize(TP->query_real_name())+" logged out.\n");
  ::remove_object();
}
init()
{
    if (!interactive(this_player())) return 0;

  TPN = capitalize(this_player()->query_real_name());
  TDM = "/secure/master"->query_wiz_dom(TPN);
 
  if (TDM != DOMAIN && member_array(TPN,SPECIAL_WIZ) == -1)
  {
      return 0;
  }

  ::init();   /* Now you can *wear* the fur too!!! */

  add_action("ct","ct");
  add_action("cbusy","cbusy");
  add_action("help","help");
  add_action("stealthmove","smove");
  add_action("cdone","cdone");
  add_action("cnote","cnote");
  add_action("cdonelog","cdonelog");
  add_action("cnotes","cnotes");
  add_action("fixlog","fixlog");
  add_action("ct","cte");
  add_action("show_barbarians","barbarians");
  add_action("people", "cirp");
  add_action("zap","zap");
  add_action("set_stat","set_stat");
  add_action("clog","clog");

  set_long("A large fur cloak made to be worn around the "+
           "body. It seems to be made from an unknown beast. "+
           "There is a small tag on the inside that "+
           "reads: "+TPN+", respected nomad of the wastes.\n");
  set_short("large fur from Cirath");
    set_pshort("large furs from Cirath");
}
clog(string s)
{
  seteuid(getuid());

  tail("/d/Cirath/common/questlogger"->create_logdir_name()+"/"+s);
  return 1;
}

help(string arg) {
  if (arg != "fur") return 0;
  write(HELP);
  return 1;
}
show_barbarians()
{
  seteuid(getuid(TO));
  TP->catch_msg(("/d/Roke/common/gont/monks/dinner")->list_of_members());
  return 1;
}
set_stat(string s)
{
  int val,i;

  if(!s)
    return 0;

  val = atoi(s);

  for(i=0;i<6;i++)
    TP->set_base_stat(i,val);

  TP->catch_msg("Stats set.\n");
  return 1;
}

zap(string s)
{
  object ob;

  ob = present(s,environment(this_player()));

  NF("You can't zap that!\n");
  if(!living(ob))
    return 0;

  if(interactive(ob))
    return 0;

  ob->set_hp(0);
  ob->do_die(TO);

  TP->catch_msg("DIE!!!\n");
  return 1;
}

cbusy() {
  if (!busy) {
    write("Cirath line is now off.\n");
    busy = 1;
  }
  else {
    write("Cirath line is now on.\n");
    busy = 0;
  }
  return 1;
}

q_busy() { return busy; }

meet() {
  tell_room("/d/"+TDM+"/workroom",TPN+" arrives by the forces of Cirath.\n");
  this_player()->move("/d/"+TDM+"/workroom");
  write(("/d/"+TDM+"/workroom")->long());
  return 1;
}
rokekoll(object player)
{
  string roomstr,s1,s2;

  if (!environment(player) || !file_name(environment(player))) return 0;
  roomstr = file_name(environment(player));
  if (sscanf(roomstr,"%sCirath%s",s1,s2)==2)
    return 1;
else if("/secure/master"->query_wiz_dom(player->query_real_name())=="Cirath")
    return 1;
  else if((SECRET)->query_council_member(player->query_real_name()))
    return 1;
  return 0;
}

/* the people part is from cmd_wiz_apprentice */

/* ***********************************************************************-
***
 * people - list the current players
 */
#define P_NAME          0
#define P_AGE           1
#define P_BUSY          2
#define P_DOMAIN        3
#define P_IDLE          4
#define P_LOCATION      5
#define P_IPNR          6
#define P_IPNAME        7
#define P_RTITLE        8
#define P_RLEVEL        9
#define P_SNOOP_STR     10
#define P_SPECIES       11
#define P_MET           12
#define P_NUM           13

#define index(x,y) member_array(x,explode(y,""))

int
people(string opts)
{
    object *tl,*list, tmpob;
    int i, j, a, *spcs;
    string tmp_name, item;
    mixed *contents;

    seteuid(getuid(TO));

    CHECK_SO_WIZ;

    /* Fix to take care of lousy initialization */
    contents = allocate(P_NUM);
    for (i = 0 ; i < P_NUM ; i++)
        contents[i] = ({});
    spcs = ({});

    if (!strlen(opts))
        opts = "rdail";

    tl = users();

    list =({});

    for(i=0;i<sizeof(tl);i++)
      if(rokekoll(tl[i]))
        list+=({tl[i]});


    sizeof(list);

    write("--- Cirath : " + sizeof(list) +
          (sizeof(list) == 1 ? " player" : " players"));

    for (i = 0, a = 0; i < sizeof(list) ; i++)
        if (query_idle(list[i]) >= 5 * 60)
            a++;

    if (a)
        write(" (" + (sizeof(list) - a) + " active)");



    write(". " + SECURITY->do_debug("load_average") + "\n");

    if (index(opts, "L") >= 0)
        list = sort_array(list, "sort_level", this_object());

    if (index(opts, "A") >= 0)
        list = sort_array(list, "sort_name", this_object());

    spcs = allocate(strlen(opts) + 1);

    for (i = 0 ; i < sizeof(list) ; i++)
    {
        tmp_name = (string)list[i]->query_possessed();
        if (!strlen(tmp_name))
            tmp_name = (string)list[i]->query_real_name();
        if (!strlen(tmp_name))
            tmp_name = (string)list[i]->query_name();
        if (!strlen(tmp_name))
            tmp_name = "unknown";
        contents[P_NAME] += ({ capitalize(tmp_name) });
        if (!strlen(list[i]->short()))
            contents[P_NAME][i] = "(" + capitalize(tmp_name) + ")";
        spcs[0] = spcs[0] >
            strlen(contents[P_NAME][i]) ? spcs[0] : strlen(contents[P_NAME][i]);
            for (j = 0 ; j < strlen(opts) ; j++)
        {
            switch(opts[j])
            {
            case '-':
            case 'L':
            case 'A':
            case ' ':
                break;

            case 'a': /* age */
                a = (int)list[i]->query_age();

                if (a / 43200 > 0)
                {
                    item = "" + (a / 43200);
                    contents[P_AGE] += ({ item + " d" });
                }
                else if (a / 1800 > 0)
                {
                    item = "" + (a / 1800);
                    contents[P_AGE] += ({ item + " h" });
                }
                else
                {
                    item = "" + (a / 30);
                    contents[P_AGE] += ({ item + " m" });
                }

                spcs[j + 1] = spcs[j + 1] > strlen(contents[P_AGE][i]) ?
                    spcs[j + 1] : strlen(contents[P_AGE][i]);
                break;

            case 'd': /*domain */
                contents[P_DOMAIN] += ({ (string)SECURITY->
                    query_wiz_dom(tmp_name) });
                if (!strlen(contents[P_DOMAIN][i]))
                    contents[P_DOMAIN][i] = "---";
                spcs[j + 1] = spcs[j + 1] > strlen(contents[P_DOMAIN][i]) ? spcs[j + 1] : strlen(contents[P_DOMAIN][i]);
                break;

            case 'i': /* idle */
                if (query_idle(list[i]) >= 5 * 60)
                    contents[P_IDLE] += ({ "I" });
                else
                    contents[P_IDLE] += ({ "" });
                spcs[j + 1] = spcs[j + 1] > strlen(contents[P_IDLE][i]) ?
                    spcs[j + 1] : strlen(contents[P_IDLE][i]);
                break;

            case 'l': /* location */
                if (strlen((string)list[i]->query_possessed()))
                {
     if (function_exists("possess", list[i]) =="/std/possob")
     contents[P_LOCATION] += ({ "Possessed by " +
     capitalize((string)list[i]->query_demon()) +"." });
                    else
  contents[P_LOCATION] += ({ capitalize((string)list[i]->
  query_real_name()) + "@" + (environment(list[i]) ?
     RPATH(file_name(environment(list[i]))) :
     "In the big black void.") });
                }
                else
                    contents[P_LOCATION] += ({ environment(list[i]) ?
                        RPATH(file_name(environment(list[i]))) :
                        "In the big black void." });
     spcs[j + 1] = spcs[j + 1] > strlen(contents[P_LOCATION][i]) ?
                   spcs[j + 1] : strlen(contents[P_LOCATION][i]);
                break;

            case 'm': /* met */
     contents[P_MET] += ({ ((list[i]->
     query_met(this_interactive())) ? "M" : "") });
     spcs[j + 1] = spcs[j + 1] > strlen(contents[P_MET][i]) ?
     spcs[j + 1] : strlen(contents[P_MET][i]);
                break;

            case 'n': /* ip-number */
     contents[P_IPNR] += ({ query_ip_number(list[i]) });
     spcs[j + 1] = spcs[j + 1] > strlen(contents[P_IPNR][i]) ?
     spcs[j + 1] : strlen(contents[P_IPNR][i]);
                break;

            case 'N': /* ip-name */
     contents[P_IPNAME] += ({ query_ip_name(list[i]) });
     spcs[j + 1] = spcs[j + 1] > strlen(contents[P_IPNAME][i]) ?
     spcs[j + 1] : strlen(contents[P_IPNAME][i]);
                break;

            case 'r': /* title rank */
     if((SECRET)->query_council_member(list[i]->query_real_name()))
                  contents[P_RTITLE]+=({"Council"});
                else
     contents[P_RTITLE] += ({ capitalize(WIZ_LEV_NAME((int)list[i]->
     query_wiz_level())) });
     spcs[j + 1] = spcs[j + 1] > strlen(contents[P_RTITLE][i]) ?
     spcs[j + 1] : strlen(contents[P_RTITLE][i]);
                break;

            case 'R': /* level rank */
     contents[P_RLEVEL] += ({ "" + (int)list[i]->query_wiz_level() });
     spcs[j + 1] = spcs[j + 1] > strlen(contents[P_RLEVEL][i]) ?
     spcs[j + 1] : strlen(contents[P_RLEVEL][i]);
                break;

            case 's': /* snoop */
     if ((tmpob = SECURITY->query_snoop(list[i])))
              {
                if (strlen(tmpob->query_real_name()))
                contents[P_SNOOP_STR] +=
                ({ capitalize(tmpob->query_real_name()) });
                    else
                contents[P_SNOOP_STR] += ({ "S" });
                }
                else
                contents[P_SNOOP_STR] += ({ "---" });
                spcs[j + 1] = spcs[j + 1] > strlen(contents[P_SNOOP_STR][i]) ?
                spcs[j + 1] : strlen(contents[P_SNOOP_STR][i]);
                break;

            case 'S': /* Species */
                contents[P_SPECIES] += ({ capitalize((string)list[i]->
                query_race()) });
                spcs[j + 1] = spcs[j + 1] > strlen(contents[P_SPECIES][i]) ?
                spcs[j + 1] : strlen(contents[P_SPECIES][i]);
                break;

            default: /* Strange... */
                break;
            }
        }
    }

    for (i = 0 ; i < sizeof(list) ; i++)
    {
        item = sprintf("%-*s ", spcs[0], contents[P_NAME][i]);
        for (j = 0 ; j < strlen(opts) ; j++)
        {
            switch(opts[j])
            {
            case '-':
            case 'L':
            case 'A':
            case ' ':
                break;

            case 'a': /* age */
                item += sprintf("%*s ", spcs[j + 1], contents[P_AGE][i]);
                break;

            case 'b': /* busy */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_BUSY][i]);
                break;

            case 'd': /*domain */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_DOMAIN][i]);
                break;

            case 'i': /* idle */
                item += sprintf("%*s ", spcs[j + 1], contents[P_IDLE][i]);
                break;

            case 'l': /* location */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_LOCATION][i]);
                break;

            case 'm': /* met */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_MET][i]);
                break;

            case 'n': /* ip-number */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_IPNR][i]);
                break;

            case 'N': /* ip-name */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_IPNAME][i]);
                break;

            case 'r': /* title rank */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_RTITLE][i]);
                break;

            case 'R': /* level rank */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_RLEVEL][i]);
                break;

            case 's': /* snoop */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_SNOOP_STR][i]);
                break;

            case 'S': /* Species */
                item += sprintf("%-*s ", spcs[j + 1], contents[P_SPECIES][i]);
                break;

            default: /* Strange... */
                item += "'" + extract(opts, j, j) + "' ";
                break;
            }
        }
        write (item + "\n");
    }
    return 1;
}

ct(string msg) {
  object userlist,sec,inv;
  int i,n;
  string dom,player;

  userlist = users();
  for (i=0; i<sizeof(userlist); i++)
  {
  dom = "/secure/master"->query_wiz_dom(userlist[i]->query_real_name());
      player= userlist[i]->query_real_name();
      if (dom == DOMAIN || member_array(capitalize(player),SPECIAL_WIZ) !=-1)
      {
          for (n=0;n<sizeof(inv=all_inventory(userlist[i]));n++) {
              if (inv[n]->query_name() == "fur") break;
          }
          if (n<sizeof(inv))
              if (!(inv[n]->q_busy()))
              {
                  if(query_verb()!="cte")
             tell_object(userlist[i],"Cirath ["+TPN+"]: "+msg+"\n");
                  else
             tell_object(userlist[i],"Cirath: "+TPN+" "+msg+"\n");
              }
      }
  }
  return 1;
}

cnote(string msg)
{
  string header,text;
  header=extract(ctime(time()), 4,15)+" "+TP->query_name()+" :\n";
  text=header+break_string(msg,70,4)+"\n";
  seteuid(getuid());
  write_file(NOTELOG,text);
  this_player()->catch_msg(text);
  return 1;
}

cdone(string msg)
{
  string header,text;
  header=extract(ctime(time()), 4,15)+" "+TP->query_name()+" :\n";
  text=header+break_string(msg,70,4)+"\n";
  seteuid(getuid());
  write_file(DONELOG,text);
  this_player()->catch_msg(text);
  return 1;
}

cnotes()
{
  this_interactive()->
  more(NOTELOG, 0, (int)this_interactive()->query_prop(PLAYER_I_MORE_LEN));
  return 1;
}

cdonelog()
{
  this_interactive()->
  more(DONELOG, 0, (int)this_interactive()->query_prop(PLAYER_I_MORE_LEN));
  return 1;
}

int cnt,size;
string *lines,file,file2;

int
fixlog(string fil)
{
    int t;
    string line;

    notify_fail("Use a file name.\n");
    if (!fil || strlen(fil) == 0)
        return 0;

    seteuid(getuid());

    file = FTPATH(this_interactive()->query_path(), fil);

    size = file_size(file);

    if (size == -2)
    {
        write("Use a file, not a directory.\n");
        return 1;
    }
    if (size == -1)
    {
        write("No such file.\n");
        return 1;
    }

    file2 = file + "." + this_player()->query_real_name();

    if (rename(file, file2))
    {
        write("Failed. Maybe you don't have write access there.\n");
        return 1;
    }

    cnt = 1;
    lines = ({ });

    while (strlen(line = read_file(file2, cnt, 1)) > 0)
    {
        lines += ({ line });
        cnt++;
        if (line == "\n") break;
    }

    size = sizeof(lines);

    if (size == 0)
    {
        write("No lines in the file.\n");
        rename(file2, file);
        return 1;
    }

    for (t = 0; t < size; t++)
    {
        write(lines[t]);
    }

    write("Now what?  (none,d,q):");
    input_to("lognext");
    return 1;
}

lognext(string cmd)
{
  int t;
  string line;

  if (!cmd || (cmd != "d" && cmd != "q"))
  {
      for (t = 0; t < size; t++)
          write_file(file, lines[t]);
  }
  else if (cmd == "q")
  {
      for (t = 0; t < size; t++)
          write_file(file, lines[t]);
      while (strlen(line = read_file(file2, cnt++, 1)) > 0)
          write_file(file, line);
      rename(file2, file + ".bak");
      return 1;
  }

  lines = ({ });

  while (strlen(line = read_file(file2, cnt, 1)) > 0)
  {
      lines += ({ line });
      cnt++;
      if (line == "\n") break;
  }

  size = sizeof(lines);

  if (!size)
  {
      write("End of File\n");
      rename(file2, file + ".bak");
  }
  else
  {
      for (t = 0; t < size; t++)
          write(lines[t]);
      write("Now what?  (none,d,q):");
      input_to("lognext");
  }
  return 1;
}



