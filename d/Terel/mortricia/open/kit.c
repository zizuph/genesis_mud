inherit "cmd/std/command_driver";

#include "/secure/std.h"
#include "/sys/macros.h"
#include "/sys/filepath.h"
#include "/sys/composite.h"
#include "/sys/stdproperties.h"
#include "/sys/money.h"

/* This defines and globals are needed for 'fget', 'fput' & 'fdel' */
#define OP_FGET 1
#define OP_FPUT 2
#define OP_FDEL 3
string *files, dfrom, dto;
int busy, operation, index, count;


get_soul_id() { return "Nosferatu's survival kit"; }

query_tool_soul() { return 1; }

query_cmdlist() {
  return ([
    "update"    : "do_update",
    "light"     : "do_light",
/*    "exec"      : "do_exec", */
    "fget"      : "do_fget",
    "fput"      : "do_fput",
    "fdel"      : "do_fdel",
    "money"     : "do_money",
    "pval"      : "do_value",
    "bomb"      : "do_bomb",
    "peace"     : "do_peace",
    "whereis"   : "do_whereis",
    "help"      : "do_help"
  ]);
}

is_wiz() {
  if (WIZ_CHECK < WIZ_NORMAL) return 0;
  if (this_interactive() != this_player()) return 0;
  return 1;
}

is_player(obj) {
  string name;

  if (!(name = obj->query_real_name())) return 0;
  return obj == find_player(name);
}

do_value(str) {
  int i, val, sum;
  object ob, *stuff;
  string sho;

  if (!is_wiz()) return 0;
  if (!str) return 0;
  ob = find_player(str);
  if (ob) write("Object: " + file_name(ob) + " (interactive)\n");
  else {
    ob = find_living(str);
    if (ob) write("Object: " + file_name(ob) + "\n");
    else {
      ob = present(str, environment(this_player()));
      if (ob) write("Object: " + file_name(ob) + "\n");
      else {
        write("Could not locate '" + str + "'.\n");
        return 1;
      }
    }
  }
  val = 0;
  stuff = deep_inventory(ob);
  write("Living/object " + ob->query_name() + " has:\n");
  write("----------------------------------------------------\n");
  for(i=0; i<sizeof(stuff); i++) {
      sho = stuff[i]->short();
      if(!sho) {
	  sho = stuff[i]->query_name();
	  sho = stuff[i]->query_adj() + " " + sho;
      }
      if(!sho) sho = "(invisible)";
      val = stuff[i]->query_value();
      if (val <= 0) val = stuff[i]->query_prop(OBJ_I_VALUE);
      sum += val;
      write("   Item(s): " + sho + "   Value: " + val + "\n");
  }
  write("----------------------------------------------------\n");
  write("Total value of: " + sum + "cc\n\n");
  return 1;
}

do_whereis(str) {
  object ob;
  string env;

  if (!is_wiz()) return 0;
  if (!str) return 0;
  ob = find_player(str);
  if (ob) write("Object: " + file_name(ob) + " (interactive)\n");
  else {
    ob = find_living(str);
    if (ob) write("Object: " + file_name(ob) + "\n");
    else {
      write("Could not locate '" + str + "'.\n");
      return 1;
    }
  }
  ob = environment(ob);
  if (ob) {
    env = file_name(ob);
    if (ob->short()) env += " (" + ob->short() + ")";
  }
  else env = "none";
  write("Environment: " + env + "\n");
  return 1;
}
    
do_money(str) {
  int *coins, *in, i;

  if (!is_wiz()) return 0;
  if (str) {
    in = allocate(4);
    if (sscanf(str, "%d %d %d %d", in[0], in[1], in[2], in[3]) != 4) {
      in[3] = 0;
      if (sscanf(str, "%d %d %d", in[0], in[1], in[2]) != 3) {
        in[2] = 0;
        if (sscanf(str, "%d %d", in[0], in[1]) != 2) {
          in[1] = 0;
          if (!sscanf(str, "%d", in[0])) {
            notify_fail("Usage: money <cc> <sc> <gc> <pc>\n");
            return 0;
          }
        }
      }
    }
    coins = MONEY_COINS(this_player());
    for (i = 0; i < sizeof(MONEY_TYPES); i++) {
      MONEY_MOVE(coins[i], MONEY_TYPES[i], this_player(), 0);
      if (in[i]) MONEY_MAKE(in[i], MONEY_TYPES[i])->move(this_player());
    }
  }
  coins = MONEY_COINS(this_player());
  write("You are carrying:\n");
  for (i = 0; i < sizeof(MONEY_TYPES); i++)
    write(sprintf("%11s: %6d\n", MONEY_TYPES[i], coins[i]));
  write(sprintf("%11s: %6d\n", "total value", MONEY_MERGE(coins)));
  return 1;
}

do_peace(str) {
  object *obarr, *elist;
  int i, count;

  if (!is_wiz()) return 0;
  if (str) return 0;
  obarr = all_inventory(environment(this_player()));
  count = 0;
  for (i = 0; i < sizeof(obarr); i++) {
    if (!function_exists("query_enemy", obarr[i])) continue;
    elist = obarr[i]->query_enemy(-1);
    if (!sizeof(elist)) continue;
    obarr[i]->stop_fight(elist);
    count++;
  }
  if (!count) {
    write("There is no fighting here.\n");
    return 1;
  }
  write("You stop the fighting in the room.\n");
  say(QCTNAME(this_player()) + " stops the fighting in the room.\n");
  return 1;
}

do_bomb(str) {
  int count, i, d, dest;
  string name;
  object *obs;

  if (!is_wiz()) return 0;
  if (str) return 0;
  obs = all_inventory(environment(this_player()));
  count = 0;
  dest = 1;
 /* while (dest) { */
    dest = 0;
    for (i = 0; i < sizeof(obs); i++) {
      if (is_player(obs[i])) continue;
      name = obs[i]->short();
      if (!name) name = "invisible";
      write("Destructing: " + name + "\t" + file_name(obs[i]) + "\n");
      obs[i]->remove_object();
      count++;
 /*     dest = 1; */
   }
    obs = all_inventory(environment(this_player()));
/* } */
  write("Destructed " + count + " objects.\n");
  say(QCTNAME(this_player()) + " cleans up the room with a magical "+
    "gesture.\n");
  return 1;
}

do_fget(str) {
  string loadpath, path;

  if (!is_wiz()) return 0;
  if (!str) return 0;
  if (busy) {
    notify_fail("Already busy doing your command.\n");
    return 0;
  }
  loadpath = FTPATH(0, "~/load");
  if (file_size(loadpath) != -2) {
    notify_fail("No such directory: " + loadpath + ".\n");
    return 0;
  }
  path = this_player()->query_path();
  if (path == loadpath) {
    notify_fail("No point in copying to the same directory.\n");
    return 0;
  }
  do_fop(path, loadpath, str, OP_FGET);
  return 1;
}
 
do_fput(str) {
  string loadpath, path;

  if (!is_wiz()) return 0;
  if (!str) return 0;
  if (busy) {
    notify_fail("Already busy doing your command.\n");
    return 0;
  }
  loadpath = FTPATH(0, "~/load");
  if (file_size(loadpath) != -2) {
    notify_fail("No such directory: " + loadpath + ".\n");
    return 0;
  }
  path = this_player()->query_path();
  if (path == loadpath) {
    notify_fail("No point in copying to the same directory.\n");
    return 0;
  }
  do_fop(loadpath, path, str, OP_FPUT);
  return 1;
}

do_fdel(str) {
  string loadpath;

  if (!is_wiz()) return 0;
  if (!str) return 0;
  if (busy) {
    notify_fail("Already busy doing your command.\n");
    return 0;
  }
  loadpath = FTPATH(0, "~/load");
  if (file_size(loadpath) != -2) {
    notify_fail("No such directory: " + loadpath + ".\n");
    return 0;
  }
  do_fop(loadpath, 0, str, OP_FDEL);
  return 1;
}
 
static
do_fop(from, to, wild, op) {
  files = get_files(from, wild);
  if (!files) {
    write("No files.\n");
    return;
  }
  operation = op;
  dfrom = from;
  dto = to;
  busy = 1;
  index = 0;
  count = 0;
  do_fop2(1);
}

static
do_fop2(display) {
  string str;

  if (index == sizeof(files)) {
    if (operation == OP_FDEL) str = "Deleted";
    else str = "Copied";
    write("Done. " + str + " " + count + " files.\n");
    busy = 0;
    return;
  }
  if (display) write("Enter y, n or q.\n");
  switch (operation) {
    case OP_FGET: write("Copy " + dfrom + "/" + files[index] +
                        " to ~/load/ ? ");
                  break;
    case OP_FPUT: write("Copy ~/load/" + files[index] + " to " + dto +
                        "/ ? ");
                  break;
    case OP_FDEL: write("Delete ~/load/" + files[index] + "? ");
                  break;
  }
  input_to("do_fop3");
}

static
do_fop3(str) {
  string opstr;
  int rc, display;
 
  seteuid(getuid());
  str = lower_case(str);
  switch (str) {
    case "q": 
      if (operation == OP_FDEL) opstr = "Deleted";
      else opstr = "Copied";
      write("Aborted. " + opstr + " " + count + " files.\n");
      busy = 0;
      return;
    case "n": index++; break;
    case "y": case "":
      if (operation == OP_FDEL) {
        rc = rm(dfrom + "/" + files[index]);
        if (!rc) write("Failed.\n");
      }
      else rc = copy(dfrom + "/" + files[index], dto + "/" + files[index]);
      if (rc) count++;
      index++;
      break;
    default: display = 1; break;
  }
  do_fop2(display);
}

static
get_files(tmp_path, wild) {
  string *tmp;
 
  seteuid(getuid());
  tmp = get_dir(tmp_path + "/" + wild);
  if (!tmp || tmp && !sizeof(tmp)) return 0;
  tmp = filter(tmp, "get_files2", this_object(), tmp_path);
  if (tmp && !sizeof(tmp)) return 0;
  return tmp;
}
 
static
get_files2(file, tmp_path) {
  seteuid(getuid());
  if (file == "." || file == "..") return 0;
  return file_size(tmp_path + "/" + file) > 0;
}
 
static
copy(from, to) {
  string content;
 
  seteuid(getuid());
  content = read_file(from);
  if (!content) {
    write("Failed to read contents of " + from + ".\n");
    return 0;
  }
  if (file_size(to) != -1 && !rm(to)) {
    write("Failed to remove " + to + "\n");
    return 0;
  }
  if (!write_file(to, content)) {
    write("Failed to write contents to " + to + ".\n");
    return 0;
  }
  return 1;
}
 
do_update(str) {
  object obj, tmp, *players;
  string fname;

  if (str) return 0;           /* give control to wiz_cmd_normal */
  if (!is_wiz()) return 0;
  seteuid(getuid());
  obj = environment(this_player());
  fname = MASTER_OB(obj);
  if (file_name(obj) != fname) {
    notify_fail("Failed to update environment.\n");
    return 0;
  }
  players = filter(deep_inventory(obj), "is_player", this_object());
  if (!valid_update(fname, players)) {
    notify_fail("You can't update the start-location of someone in this "+
      "room.\n");
    return 0;
  }
  move_all_players(players, 0);
  obj->remove_object();
  obj = find_object(fname);
  if (obj) "secure/master"->do_debug("destroy", obj);
  if (obj) {
    notify_fail("Object could not be updated.\n");
    return 0;
  }
  write("Updating environment (" + fname + "): ");
  call_other(fname, "???");
  obj = find_object(fname);
  if (!obj) {
    notify_fail("Object could not be reloaded.\n");
    return 0;
  }
  move_all_players(players, obj);
  write("Ok.\n");
  say(QCTNAME(this_player()) + " updates the room.\n");
  return 1;
}

valid_update(room, *players) {
  int i;

  for (i = 0; i < sizeof(players); i++)
    if (room == players[i]->query_default_start_location()) return 0;
  return 1;
}

move_all_players(*players, to_room) {
  int i;

  for (i = 0; i < sizeof(players); i++) {
    if (to_room) players[i]->move(to_room);
    else players[i]->move(players[i]->query_default_start_location());
  }
}

inventory(str) {
  object who, *obarr;

  if (!is_wiz()) return 0;
  if (!str) return 0;       /* give control to misc_cmd.c */
  who = find_living(lower_case(str));
  if (!who) {
    write("No such living.\n");
    return 1;
  }
  obarr = who->subinventory(0);
  if (sizeof(obarr) > 0) {
    str = COMPOSITE_DEAD(obarr);
    write(break_string(who->query_name() + " is carrying " + str + ".\n", 76,
      2));
  }
  else write("  " + who->query_name() + " doesn't carry anything.\n");
  return 1;
}

do_light(str) {
  int mylight, roomlight, newlight;

  if (!is_wiz()) return 0;
  mylight = this_player()->query_prop(CONT_I_LIGHT);
  roomlight = environment(this_player())->query_prop(ROOM_I_LIGHT);
  if (str == "off") {
    if (roomlight <= 0) {
      notify_fail("The light in this room is already off.\n");
      return 0;
    }
    this_player()->add_prop(CONT_I_LIGHT, mylight-roomlight);
  }
  else if (str == "on") {
    if (roomlight > 0) {
      notify_fail("The light in this room is already on.\n");
      return 0;
    }
    this_player()->add_prop(CONT_I_LIGHT, mylight-roomlight+1);
  }
  else if (str) {
    if (!sscanf(str, "%d", newlight)) {
      notify_fail("Give the wanted light strength, 'on' or 'off' as "+
        "argument.\n");
      return 0;
    }
    this_player()->add_prop(CONT_I_LIGHT, mylight-roomlight+newlight);
  }
  mylight = this_player()->query_prop(CONT_I_LIGHT);
  roomlight = environment(this_player())->query_prop(ROOM_I_LIGHT);
  write("Your light strength is " + mylight + ".\n");
  write("Environmental light strength is " + roomlight + ".\n");
  return 1;
}

do_exec(str) {
  string code, fname, errormsg;
  object obj;

  if (!is_wiz()) return 0;
  if (!str) return 0;
  seteuid(getuid());
  fname = FTPATH(0, "~/exec_tmp_9251.c");
  code = "inherit \"std/object.c\";\n";
  code += "#include \"/sys/stdproperties.h\"\n";
  code += "#include \"/sys/wa_types.h\"\n";
  code += "#include \"/sys/macros.h\"\n";
  code += "#include \"/sys/formulas.h\"\n";
  code += "#include \"/sys/ss_types.h\"\n";
  code += "#include \"/sys/filepath.h\"\n";
  code += "#include \"/sys/language.h\"\n";
  code += "#include \"/sys/const.h\"\n";
  code += "#include \"/sys/money.h\"\n";
  code += "execute() { " + str + " }\n";
  rm(fname);
  write_file(fname, code);
  if (obj = find_object(fname)) "secure/master"->do_debug("destroy", obj);
  errormsg = catch(obj = clone_object(fname));
  if (!obj) {
    write("Error in loading code.\n");
    write("-> " + errormsg);
    rm(fname);
    return 1;
  }
  obj->move(this_player());
  errormsg = catch(call_other(obj, "execute"));
  if (errormsg) {
    write("Error in executing code.\n");
    write("-> " + errormsg);
    rm(fname);
    "secure/master"->do_debug("destroy", obj);
    return 1;
  }
  write("Ok.\n");
  rm(fname);
  "secure/master"->do_debug("destroy", obj);
  return 1;
}

do_help(str) {
  if (!is_wiz()) return 0;
  if (str != "kit") return 0;
  write(
"bomb               : destruct every non-player-object in your environment.\n"+
"exec <code>        : execute lpc code.\n"+
"fget <wildcard>    : copy file(s) from current directory to ~/load.\n"+
"fput <wildcard>    : copy file(s) from ~/load to current directory.\n"+
"fdel <wildcard>    : delete file(s) in ~/load.\n"+
"light [num|on|off] : change light in your environment.\n"+
"money [coins]      : make or lose money.\n"+
"pval <name>        : Find objects and their value in living.\n"+
"peace              : stop all fighting in your environment.\n"+
"update             : update \"\" = update your environment.\n"+
"whereis <name>     : find a living and tell where it is.\n\n"+
"fget, fput & fdel are meant to ease the pain of not having ftp access to\n"+
"your domain's directory. Simply make the ~/load directory and you'll be\n"+
"able to easily download an entire domain-dir...\n");
  return 1;
}
