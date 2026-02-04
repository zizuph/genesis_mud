
inherit "/std/board";
 
#define BOARDDIR    "/d/Terel/common/road/cstone"
#define BOARDLOG    "/d/Terel/log/CORNERSTONE"
static int r_remove_msg(string what_msg);

int msg_num = 13;
string board_name = BOARDDIR;
static private mixed *headers = ({ });
int remove_lvl = 1;
string remove_str = "What ?\n";

create_board() {
   remove_name( ({"board", "bulletin board", "bulletinboard" }) );
   set_name( ({ "stone", "corner stone", "cornerstone" }) );
   set_short("cornerstone");
   set_board_name(BOARDDIR);
   set_num_notes(30);
   set_anonymous(1);
   set_silent(1);
   set_show_lvl(0);
   set_remove_lvl(1);
   set_remove_str("What ?\n");
   set_err_log(BOARDLOG);
   add_item( ({ "inscription", "inscriptions" }),
      "Inscriptions generally form textual passages.  Try reading it.\n");
   add_item( "lichen", "The lichen betrays the great age of the stone.\n");
   add_item( "granite", "A very hard metamorphic rock.\n");
}


id(str) {
   string discardstr;
   int    discardint;

   return ((::id(str)) ||
           (sscanf(str, "inscripti%s %d", discardstr, discardint) == 2));
}


void init() {
   ::init();
   /* override the exclusive commands */
   add_action("Terel_remove","remove");
   add_action("Terel_read",  "read");
   add_action("Terel_read",  "mread");
   add_action("Terel_new",   "note");
   add_action("Terel_new",   "gnote");
}


status query_Terel_wizard() {
   if (this_player()->query_wiz_level() < 1) {
      return 0;
   }
   if ((this_player()->query_wiz_level() >= 35) ||
       ("/secure/master"->domain_lord(geteuid(this_object())) ==
        "/secure/master"->domain_lord(geteuid(this_player())))) {
      return 1;
   }
}



status Terel_read(string str) {
   int    possible_note;

   if (!str) {
      write("Read what?  Please 'read <title>' or 'read <number>'.\n");
   }
   if (msg_num == 0) {
      write("None of the inscriptions are legible..\n");
      return 1;
   }
   if ((str == "inscription") || (str == "inscriptions")) {
      if (msg_num == 1) {
         possible_note = 1;
      }
      write("Which inscription do you mean?  There are several..\n");
      return 1;
   }
   else if (!((sscanf(str, "%d", possible_note) == 1) ||
             (sscanf(str, "inscription %d", possible_note) == 1))) {
      for (possible_note = 0; possible_note < msg_num; possible_note ++) {
          if (lower_case(str) == lower_case(headers[possible_note][0])) {
             break;
          }
      }
      if (possible_note >= msg_num) { 
         possible_note = 0;
      }
      else {
         possible_note ++;
      }    
   }
   if (!possible_note) {
      write("Huh?  Which inscription to you want to read?\n");
      return 1;
   }
   if ((possible_note < 1) || (possible_note > msg_num)) {
      write("There are not that many inscriptions.\n");
      return 1;
   }
   possible_note --;
   write("The inscription's title is '" +  
         headers[possible_note][0] + "'.\n\n");
   if (query_verb() == "mread")
      read_msg(board_name + "/" + headers[possible_note][1], 0);
   else
      cat(board_name + "/" + headers[possible_note][1], 2);
  return 1;
}


status Terel_remove(string str) {
   if (!query_Terel_wizard()) {
      write("What ?  This is a stone, not a bulletin board!\n");
      return 1;
   }
   return r_remove_msg(str);
}


status Terel_new(string str) {
   if (!query_Terel_wizard()) {
      write("What ?  This is a stone, not a bulletin board!\n");
      return 1;
   }
   return ::new_msg(str);
}


public mixed
long() {
   string retain;
   string discard;
   string str;
   int    ind;

   /* give them a general description, & index of inscriptions */
   str = "This is a huge corner stone.  Various inscriptions have been\n" +
   "sculpted into the solid granite rock, which is covered with a deep\n" +
   "orange layer of lichen.\n";
   if (query_Terel_wizard()) {
      str += "[Wizard info, commands: note, gnote, remove, store].\n";
   }

   if (!msg_num) {
      return str + "However, none of the inscriptions are legible..\n";
   }

   if (msg_num == 1) {
      str += "There is only one inscription that you can read, however.\n";
   }
   else {
      str += "There are roughly " + msg_num + " readable inscriptions.\n";
   }
   /* display the list of inscriptions */
   ind = 0;
   while (ind < msg_num) {
      /* If '(writer, date)' is in the title, remove it */
      if (sscanf(headers[ind][0], "%s (%s)", retain, discard) == 2) {
         headers[ind][0] = retain;
      }
      str += "(" + (ind + 1) + ")\t" + headers[ind][0] + "\n";
      ind ++;
   }
   return str;
}

static int
r_remove_msg(string what_msg)
{
    string player, title, date;
    int note;

    if (!sscanf(what_msg, "%d", note)) 
        if (!sscanf(what_msg, "note %d", note))
            return 0;
    if (note < 1 || note > msg_num)
    {
        write("That message doesn't exist.\n");
        return 1;
    }
    note--;
    if ((no_special_fellow() &&
         this_player()->query_wiz_level() < remove_lvl) ||
        !query_ip_number(this_player()))
    {
        write(remove_str);
        return 1;
    }
    discard_message(headers[note][1]);
    headers = exclude_array(headers, note, note);
    msg_num--;
    write("Ok.\n");
    return 1;
}

