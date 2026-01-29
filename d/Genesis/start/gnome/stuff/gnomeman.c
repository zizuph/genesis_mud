#include "../gnome.h"
#include "language.h"

#pragma save_binary

inherit  LIB;
inherit  "/std/monster";

object  stone;
int     story_line;
string *story;

void
create_monster() {
    string story_text;
    seteuid(getuid());
    story_text = read_file(STORY_FILE);
    if (story_text) {
	story = explode(story_text, "\n");
    } else {
	story = ({ });
    }
    set_name("fooble");
    set_race_name("gnome");
    default_config_npc(16);
    story_line = -1;
}

void
init_living() {
    object ob;
    if (!stone &&
	(ob = present("myspecialdonut", this_player())) &&
	!ob->is_rocky_donut(1)) {
	stone = ob;
	call_out("found_donut", 2, this_player());
	if (story_line >= 0) {
	    remove_call_out("tell_story");
	}
    } else if (story_line < 0) {
	story_line = 0;
	call_out("tell_story", 2, this_player());
    }
}

void
tell_story(object who) {
    if (story_line >= sizeof(story)) {
	return;
    }
    call_out("tell_story", GNOME_DELAY, 0);
    if (who) {
	command("say Hello, " + who->query_name() + ".\n");
	return;
    }
    if (story[story_line] && strlen(story[story_line])) {
	command(story[story_line]);
    }
    story_line ++;
}

void
found_donut(object who) {
    if (story_line >= 0) {
	story_line = 999;
    }
    command("gasp");
    seq_new("foo");
    seq_addfirst("foo",	 ({
	"say That is a mighty interesting stone, " + who->query_name() + ".",
	"@@fixstone",
      }) );
}

void
fixstone() {
    if (!stone || !living(environment(stone))) {
	command("shrug");
	story_line = -1;
	stone      = 0;
    } 
    command("snap");
    tell_room(environment(),
	      BS("Suddenly, " +
		 LANG_POSS((string)environment(stone)->query_name()) + 
		 " " + stone->short() + " starts buzzing... lifting into " +
		 "the air... Spinning more and more rapidly and glowing " +
		 "strangely.\n"));
    command("snap");
    stone->set_phase(1);
    stone->move(environment());
    tell_room(environment(),
	      BS("In a flash of white, the stone stops and falls to the " +
		 "floor. It has changed quite dramatically!\n"));
    story_line = -1;
    stone      = 0;
}