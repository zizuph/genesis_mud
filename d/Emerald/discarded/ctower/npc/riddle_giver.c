#include <macros.h>
#include <living_desc.h>

static mapping	players;
static mapping	asked;

static mixed	riddles;
static mixed	answers;

static int	autostart;

static void start_riddle(object ob);
static void check_answer(object obj, string answer);

/*
 * Interface stuff
 */
nomask void
create_riddle(string file, int auto)
{
    string *text, *single, tmp;
    int   i, in_riddle;

    players = ([ ]);
    asked = ([ ]);
    riddles = ({ });
    answers = ({ });

    setuid();
    seteuid(getuid());
    tmp = read_file(file);
    if (tmp) {
	text = explode(tmp, "\n");
	for (single = ({ }), in_riddle=1, i=0 ; i<sizeof(text) ; i++) {
	    if (text[i] == "-") {
		in_riddle = 0;
		riddles += ({ single });
		single = ({ });
		continue;
	    }
	    else if (text[i] == "+") {
		in_riddle = 1;
		answers += ({ single });
		single = ({ });
		continue;
	    }
	    single += ({ text[i] });
	}
    }
    autostart = auto;
}

nomask void
init_riddle()
{
    object *list;
    int    i;

    players = m_delete(players, 0);
    list = m_indexes(players);
    for (i=0 ; i<sizeof(list) ; i++)
	if (!present(list[i], environment()))
	    players = m_delete(players, list[i]);
    players = m_delete(players, this_player());
    if (interactive(this_player())) {
	add_action("do_reply", "reply");
	add_action("do_reply", "answer");
	if (autostart)
      set_alarm(2.0, 0.0, &start_riddle(this_player()));
	else
	    add_action("do_ask", "ask");
    }
}

nomask void
tell(object ob, string str)
{
    ob->catch_msg(break_string(capitalize(LD_THE) + " " +
		  this_object()->query_nonmet_name() + " tells you : "+
		  str + "\n", 76));
}

/*
 * Internal functions
 */
static int
do_ask(string arg)
{
    notify_fail("Ask what?\n");
    if (arg != "riddle" && arg != "about riddle" && arg != "for riddle")
	return 0;
    write("Ok.\n");
    set_alarm(2.0, 0.0, &start_riddle(this_player()));
    return 1;
}

static int
do_reply(string arg)
{
    int qnum;

    notify_fail("Reply what?\n");
    if (!arg)
	return 0;
    qnum = players[this_player()];
    if (!qnum) {
	this_player()->catch_msg(QCTNAME(this_object()) +
				 " isn't listening.\n");
	return 1;
    }
    write("Ok.\n");
    players = m_delete(players, this_player());
    switch (qnum) {
	case 1:
      set_alarm(2.0, 0.0, &start_riddle(this_player()));
	    break;
	case 2:
      set_alarm(1.0, 0.0, &check_answer(this_player(), arg));
	    break;
    }
    return 1;
}

static void
start_riddle(object ob)
{
    int number, j;

    if (!ob || !present(ob, environment()))
	return;
    this_object()->start_riddle_hook(ob);
    if (!sizeof(riddles) || sizeof(riddles) != sizeof(answers)) {
	tell(ob, "Oh, I seem to have lost all my riddles. Be off with you.");
	return;
    }
    tell(ob, "Here is your riddle:");
    number = asked[ob->query_real_name()];
    if (number)
	number--;
    else
	number = random(sizeof(riddles));
    for (j=0 ; j<sizeof(riddles[number]) ; j++)
	write(riddles[number][j] + "\n");
    players += ([ ob : 2 ]);
    asked = m_delete(asked, ob->query_real_name());
    asked += ([ ob->query_real_name() : number+1 ]);
}

static void
check_answer(object ob, string answer)
{
    int    number, i;

    answer = lower_case(answer);
    if (!ob || !present(ob, environment()))
	return;
    number = asked[ob->query_real_name()];
    if (!number) {
	tell(ob, "I don't recall having asked you anything.");
	return;
    }
    number--;
    if (member_array(answer, answers[number]) >= 0)
	this_object()->correct_answer_hook(ob);
    else
	this_object()->wrong_answer_hook(ob);
}

/*
 * The following functions should be overridden in the inheriting object
 */
public void
start_riddle_hook(object ob)
{
    tell(ob, "Here is your riddle:");
}

public void
wrong_answer_hook(object ob)
{
    tell(ob, "That was not the correct answer.");
}

public void
correct_answer_hook(object ob)
{
    tell(ob, "That was the correct answer.");
}
