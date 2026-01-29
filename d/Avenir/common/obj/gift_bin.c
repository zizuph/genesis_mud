/*
 * - gift_bin.c  -=-  Lucius
 *
 * This rooms holds gifts in awaiting delivery
 * or pickup.
 */
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

#include "/d/Avenir/include/paths.h"
/*
 * Undefine this to turn off logging.
 */
#define GIFT_LOG  (LOG + "gifts")
#define SCROLLING_LOG(file, entry)  ((file_size(file) > 500000) ? \
    (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
    (write_file(file, ctime(time()) + ": " + entry + "\n")))
/*
 * Alarms for delivery.
 */
#define DELIVER_DELAY	itof(100 + random(20) + random(20))
/*
 * Indices to the gifts sub-mappings.
 */
#define GSENDER  0
#define GTIME    1
#define GALARM   2
#define GITEM    3
#define GMESS    4
/*
 * mapping = ([ "addressee" : ([ (int)ID : ({
 *	"sender", (int)timestamp, (object)box }), "message",
 * }), ]), ]);
 */
private mapping m_gifts = ([]);
private int alarm;
/* Prototypes */
public void mail_peeps(string from, int id);
public void deliver_gift(string from, int id);
/*
 * Maybe do some logging to check things are
 * kosher and/or working as expected.
 */
private void
log_gift(string to, string from, object gift)
{
#ifdef GIFT_LOG
    string str = from +" to "+ to +", containing:\n";

    foreach(object item : all_inventory(gift))
    {
	str += "   "+ item->short() +" ("+ file_name(item) +")\n";
	/*
	 * Indent an extra level for sub-containers, but don't
	 * recurse further than one level.
	 */
	if (item->query_prop(CONT_I_IN))
	{
	    foreach(object subitem : all_inventory(item))
	    {
		str += "      "+
		    subitem->short() +" ("+ file_name(subitem) +")\n";
	    }
	}
    }

    SCROLLING_LOG(GIFT_LOG, str);
#endif
}
/*
 * Register a new gift for a person.
 */
public int
register_gift(string from, mapping data, object gift)
{
    if (!strlen(from) || !m_sizeof(data) || !objectp(gift))
	return 0;

    string to = data["ADDRESS"];

    if (!m_sizeof(m_gifts[to]))
	m_gifts[to] = ([ ]);

    int id = m_sizeof(m_gifts[to]) + 1;

    m_gifts[to][id] = ({
	from, time(), 0, gift, data["MESSAGE"]
    });

    log_gift(to, from, gift);
    m_gifts[to][id][GALARM] = set_alarm(
	DELIVER_DELAY, 0.0, &deliver_gift(to, id));

    return id;
}
/*
 * Unregister (and optionally destroy) a gift for a person.
 */
public varargs int
unregister_gift(string whose, int id = -1, int flag = 0)
{
    if (!m_gifts[whose] || !m_gifts[whose][id])
	return 0;

    if (m_gifts[whose][id][GALARM])
	remove_alarm(m_gifts[whose][id][GALARM]);

#ifdef GIFT_LOG
    SCROLLING_LOG(GIFT_LOG, whose +" gift ["+ id +"] was "+
	(flag ? "delivered" : "claimed") +".\n");
#endif

    m_delkey(m_gifts[whose], id);
    return 1;
}

private string card_header = implode(map(({
    "  __            __                 _   __            ",
    " /__)  __/_ _  (  _ _   '_ _  _   (_  (    / _ _    _",
    "/   ()/ /(-/  __)(-/ \\//( (-_)  ()/  __)(/()(// (/_)",
    "                                        /           ",
    }), &sprintf("%|60s", )), "\n");

/*
 * Add extra bits to a gift prior to final delivery.
 */
private void
mark_gift(string who, object gift, mixed *data)
{
    if (!objectp(gift) || !sizeof(data))
	return;

    who = "To: "+ capitalize(who);

    string text = sprintf("%s\n\n %s%*s \n\n",
	card_header, who, 58 - strlen(who),
	"From: "+ capitalize(data[GSENDER]));

    /* Make sure there is actual text, and not just
     * empty lines from a blank message.
     */
    who = implode(filter(explode(data[GMESS], "\n"), strlen), "\n");

    if (strlen(who))
	text += sprintf("%'~*'61s\n\n%s\n", "", data[GMESS]);

    gift->set_extra(text);
}
/*
 * Someone wants goodies!
 */
public varargs int
receive_gifts(object who, int flag)
{
    if (!objectp(who))
	return 0;

    string whom = who->query_real_name();

    if (!m_gifts[whom])
	return 0;

    int count;

    foreach(int id, mixed data : m_gifts[whom])
    {
	object gift = data[GITEM];

	mark_gift(whom, gift, data);

	if (gift->move(who))
	    gift->move(who, 1);

	count++;
	unregister_gift(whom, id, flag);
    }

    return count;
}
/*
 * Deliver presents!
 */
public void
deliver_gift(string who, int id = -1)
{
    if (!strlen(who))
	return;

    if (!m_gifts[who] || !m_gifts[who][id])
	return;

    m_gifts[who][id][GALARM] = 0;

    object player = find_player(who);

    if (!objectp(player) || player->query_linkdead())
    {
	m_gifts[who][id][GALARM] = set_alarm(
	    (DELIVER_DELAY / 2.0), 0.0, &mail_peeps(who, id));
	return;
    }

    int count = receive_gifts(player, 1);
    if (!count) /* Shouldn't be possible, but... */
	return;

    string clr = one_of_list(({
	"green", "yellow", "black", "red", "violet"
    }));
    
    string adj = one_of_list(({"efficacious", "flustered", "lively", 
	"energetic", "efficient", "busy", "bustling", "teenaged", "gangly",
	"young", "adolescent", "brisk", "peppy", "spry", "zippy", "lanky",
    }));

    player->catch_tell(capitalize(LANG_ADDART(adj)) +" waif runs "+
	"up to you, stuffing "+ LANG_NUM2WORD(count) +" package"+
	(count > 1 ? "s" : "") +" into your arms before "+
	"speeding off with a tip of his sporty "+ clr +" beret.\n");

    tell_room(environment(player),
	capitalize(LANG_ADDART(adj)) +" waif runs up to "+ QTNAME(player) +
	", stuffing "+ (count > 1 ? "packages" : "a package") +
	" into "+ player->query_possessive() +" arms then "+
	"speeding off with a tip of his sporty "+ clr +
	" beret.\n", ({ player }), player);
}
/*
 * Recipient wasn't available, hold and
 * send mail notifications.
 */
#define CREATE_MAIL(to, body) reader->create_mail( \
    "Delivery Notification", "PorterGuild", to, "", body)

private string mail_footer = implode(map(({
    "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+",
    "|P|o|r|t|e|r| |S|e|r|v|i|c|e|s| |o|f| |S|y|b|a|r|u|s|",
    "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+",
    }), &sprintf("%|60s", )), "\n");

public void
mail_peeps(string who, int id = -1)
{
    if (!strlen(who))
	return;

    if (!m_gifts[who] || !m_gifts[who][id])
	return;

    m_gifts[who][id][GALARM] = 0;

    object reader = "/secure/mail_reader"->get_this_object();
    string text = "This mail is to inform you that "+
	capitalize(who) +" was unavailable at the time of "+
	"delivery. The package is being held by the Porters "+
	"Guild and "+ capitalize(who) +" has been notified that "+
	"it may be claimed by visiting any available Guild "+
	"representative.";

    /* Sender mail. */
    CREATE_MAIL(m_gifts[who][id][GSENDER], sprintf("%s\n\n%s",
	    break_string(text, 60, 3), mail_footer));

    text = "This mail is to inform you that you have a delivery "+
	"awaiting pickup from any available Porters Guild "+
	"member. This package will only be held until "+
	"the next Armageddon cleans the realms, after which it "+
	"will be impossible to recover.";

    /* Recipient mail. */
    CREATE_MAIL(who, sprintf("%s\n\n%s",
	    break_string(text, 60, 3), mail_footer));
}
/*
 * Suffer no living objects to enter.
 */
public int
prevent_enter(object ob)
{
    if (living(ob))
	return !ob->query_wiz_level();

    return 0;
}
/*
 * Setup the minimum.
 */
static void
create_room(void)
{
    set_short("gifting portal");
    set_long("Gifts are stacked all over the floor, walls, everywhere!\n");

    add_prop(ROOM_M_NO_SCRY,		1);
    add_prop(ROOM_M_NO_STEAL,		1);

    add_prop(ROOM_M_NO_MAGIC,		1);
    add_prop(ROOM_M_NO_ATTACK,		1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK,	1);

    add_prop(ROOM_M_NO_TELEPORT,	1);
    add_prop(ROOM_M_NO_TELEPORT_TO,	1);
    add_prop(ROOM_M_NO_TELEPORT_FROM,	1);

    add_prop(ROOM_I_NO_EXTRA_DESC,	1);
    add_prop(ROOM_I_NO_EXTRA_ITEM,	1);
    add_prop(ROOM_I_NO_EXTRA_EXIT,	1);
}

public void
debug_alarms(void)
{
    foreach(mixed *arr : get_all_alarms())
    {
	write(sprintf("  %d : %f  [%s]\n",
		arr[0], arr[2], arr[1]));
    }
}
