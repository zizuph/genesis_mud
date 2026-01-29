#pragma save_binary

/*
 *	Inherit this in your captain if the
 *	Captain's ship is landing in Pelargir.
 *
 *	Add a call in create_captain() to:
 *	set_up_pelargir_tour();
 *
 *	Update the number of captains in
 *	/d/Gondor/pelargir/misc/tournote.c so the tour
 *	doesn't screw up!
 *
 *	Olorin, July 1995
 */
#define CAPTAIN_TOUR	1

string reply_pelargir_tour();

void
set_up_pelargir_tour()
{
    this_object()->add_ask(({"report", "reports", "corsair", "corsairs", }),
        "@@reply_pelargir_tour:" + file_name(this_object()) + "@@");
}

string
reply_pelargir_tour()
{
    object  note,
            tp = this_player();

    if (!objectp(note = present("Pelargir_Tour_Note", tp)) ||
        (note->query_tour_no() != CAPTAIN_TOUR))
        return this_object()->check_call(this_object()->query_default_answer());

    if (member_array(this_object()->query_name(), note->query_cnames()) > -1)
    {
        this_object()->command("peer " + tp->query_real_name());
	this_object()->command("say You have been here before, haven't you?");
	this_object()->command("say How often do you want my reports?");
	this_object()->command("say Isn't once enough?");
	this_object()->command("sigh");
	this_object()->command("emote mumbles something about incompetent nincompoops.");
	return "";
    }

    this_object()->command("smile " + tp->query_real_name());
    this_object()->command("say Ah, you come from Carastur, the Lord Councillor?");
    this_object()->command("emote takes the tour note.");
    this_object()->command("emote scribbles a short report on the tour note.");
    this_object()->command("emote gives the tour note back.");
    note->add_captain(this_object()->query_name());
    if (note->query_tour_done())
    {
        this_object()->command("say You have completed the task.");
        this_object()->command("say Go back to Carastur and bring him the reports!");
    }
    return "";
}
