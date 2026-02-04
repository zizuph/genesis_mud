inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help";

#include "../guild_defs.h"
#include <composite.h>
#include <options.h>

#define CLEANLOG_DISABLED
#define SET_MUSE_DISABLED

void
create()
{
    setuid();
    seteuid(getuid());

    read_help_dir(MINSTREL_HELP_DIR, "chelp");
    set_help_type(({ "cycle" }));
}

string *
replace_soul()
{
    object ob = previous_object();

    // Eliminate the soul from those who shouldn't have it
    if (!ob || (!ob->query_wiz_level() && !ob->query_cycle_member()))
    {
        return ({});
    }

    return 0;
}

string get_soul_id() { return "Minstrel Cycle"; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
    return ([
                "mcreview" : "mcreview",
                "mcmembers" : "mcmembers"
            ]) + help_cmdlist();
}

public varargs void
mcreview_list2(object reviewer,
               int max,
               string *songs,
               int cnt = 0,
               string list = "")
{
    string fmt = "%1s %" + strlen(sizeof(songs) + "") + "d. %-=30s %-11s %|9s %-=11s\n";

    if (!strlen(list))
    {
        string fmt2 = "  %" + strlen(sizeof(songs) + "") + "s  %-30s %-11s %|9s %-11s\n";
        list = "* Songs which you have already reviewed\n\n" +
               sprintf(fmt2, "", "Title", "Author", "Aprv/Deny", "Comments") +
               "=======================================================================\n";
    }

    setuid();
    seteuid(getuid());

    for (; (cnt < max) && (cnt < sizeof(songs)); cnt++)
    {
        string *approve = SONG_INDEX->query_ballad_approve_votes(songs[cnt]);
        string *deny = SONG_INDEX->query_ballad_deny_votes(songs[cnt]);
        int reviewed =
            (member_array(reviewer->query_real_name(), approve) != -1) ||
             (member_array(reviewer->query_real_name(), deny) != -1);

        list += sprintf(fmt,
                        reviewed ? "*" : " ",
                        cnt + 1,
                        SONG_INDEX->query_title(songs[cnt]),
                        SONG_INDEX->query_author(songs[cnt]),
                        sizeof(approve) + "/" + sizeof(deny),
                        implode(map(SONG_INDEX->query_ballad_commenters(songs[cnt]), capitalize), ", "));
    }

    if (cnt >= sizeof(songs))
    {
        reviewer->catch_tell(list);
        return;
    }

    set_alarm(0.5, 0.0, &mcreview_list2(reviewer, max, songs, cnt, list));
}

public int
mcreview_list(string str)
{
    string *songs;

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->query_ballad_submissions();
    if (!sizeof(songs))
    {
        write("There are no songs awaiting review.\n");
        return 1;
    }

    if (sizeof(songs) > 20)
    {
        int t = (sizeof(songs) / 20 / 2 + 1);
        write("There are a large number of songs awaiting review. Please " +
              "wait while a report is generated (approximately " + t +
              ((t == 1) ? " second" : " seconds") + ")....\n");
    }

    mcreview_list2(this_player(), 20, songs);
    return 1;
}

public int
mcreview_read(string str)
{
    mixed song;
    string *songs;
    string song_file, txt;
    int songnum, i;

    if (!strlen(str))
    {
        notify_fail("Usage: mcreview read text <song>\n" +
                    "       mcreview read comments <song>\n\n" +
                    "<song> should be the exact song title or the song " +
                    "number as given in \"mcreview list\"\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (sscanf(str, "text %s", song))
    {
        songs = SONG_INDEX->query_ballad_submissions();

        if (sscanf(song, "%d", songnum))
        {
            if ((songnum > 0) && (songnum <= sizeof(songs)))
            {
                song_file = songs[songnum - 1];
            }
            // else...maybe there's a song actually titled "400" or something,
            // so just pass here
        }

        if (!song_file)
        {
            string index = SONG_INDEX;
            string lcsong = implode(map(explode(song, ""), lower_case), "");
            string fname = SONG_INDEX->title_to_filename(song);
            string *song_matches = regexp(songs,
                                          "^" + BALLAD_SONGS_SUBMISSION_DIR +
                                          fname + "(_[0-9][0-9]*)*(\\.[^\\.]*)*$");
            song_matches = filter(song_matches, &operator(==)(lcsong) @
                                                &index->query_lc_title());

            if (sizeof(song_matches) > 1)
            {
                write("More than one song matches. Please be more specific.\n");
                return 1;
            }

            if (sizeof(song_matches) < 1)
            {
                write("No matching song was found.\n");
                return 1;
            }

            song_file = song_matches[0];
        }

        txt = SONG_INDEX->query_title(song_file) + " by " +
              SONG_INDEX->query_author(song_file) + "\n\n" +
              SONG_INDEX->query_text(song_file) + "\n";

        this_player()->more(txt);
        return 1;
    }
    else if (sscanf(str, "comments %s", song))
    {
        string comments;
        string *commenters;

        songs = SONG_INDEX->query_ballad_submissions();

        if (sscanf(song, "%d", songnum))
        {
            if ((songnum > 0) && (songnum <= sizeof(songs)))
            {
                song_file = songs[songnum - 1];
            }
            // else...maybe there's a song actually titled "400" or something,
            // so just pass here
        }

        if (!song_file)
        {
            string index = SONG_INDEX;
            string lcsong = implode(map(explode(song, ""), lower_case), "");
            string fname = SONG_INDEX->title_to_filename(song);
            string *song_matches = regexp(songs,
                                          "^" + BALLAD_SONGS_SUBMISSION_DIR +
                                          fname + "(_[0-9][0-9]*)*(\\.[^\\.]*)*$");
            song_matches = filter(song_matches, &operator(==)(lcsong) @
                                                &index->query_lc_title());

            if (sizeof(song_matches) > 1)
            {
                write("More than one song matches. Please be more specific.\n");
                return 1;
            }

            if (sizeof(song_matches) < 1)
            {
                write("No matching song was found.\n");
                return 1;
            }

            song_file = song_matches[0];
        }

        commenters = SONG_INDEX->query_ballad_commenters(song_file);
        for (i = 0, txt = ""; i < sizeof(commenters); i++)
        {
            txt += "(" + capitalize(commenters[i]) + ") " + 
                   SONG_INDEX->query_ballad_comments(song_file, commenters[i]) + "\n";
        }

        this_player()->more(txt);
        return 1;
    }
    else
    {
        notify_fail("Usage: mcreview read text <song>\n" +
                    "       mcreview read comments <song>\n\n" +
                    "<song> should be the exact song title or the song " +
                    "number as given in \"mcreview list\"\n");
        return 0;
    }
}

public void
done_approving(string song, string text)
{
    string *approve;
    string name;

    setuid();
    seteuid(getuid());

    // It's unlikely, but possible, that the song has been accepted while
    // we were editing so we should check for that.

    if (member_array(song, SONG_INDEX->query_ballad_submissions()) == -1)
    {
        write("The song is no longer available for approval. Perhaps it has " +
              "been approved already.\n");
        return;
    }

    name = this_player()->query_real_name();

    if (strlen(text) && sizeof(regexp(({ text }), "[^ \n]")))
    {
        SONG_INDEX->add_ballad_comments(song, name, text);
    }

    SONG_INDEX->add_ballad_approve_vote(song, name);

    approve = SONG_INDEX->query_ballad_approve_votes(song) || ({});

    write("You give the song the highest praise possible, " +
          "recommending it for addition to the Ballads.\n");

    if (sizeof(approve) > 2)
    {
        write("Three members of the Cycle have deemed this "
            + "song worthy to be a Ballad; so shall it "
            + "be!\n");
        SONG_INDEX->approve_ballad(song);
    }
}

public void
reply_approve(string song, int reply)
{
    if (reply == 0)
    {
        write("Ok.\n");
        return;
    }

    if (reply == -1)
    {
        write("Timeout. Try again if you wish to approve the song.\n");
        return;
    }

    if (reply == 1)
    {
        string *approve;

        setuid();
        seteuid(getuid());

        approve = SONG_INDEX->query_ballad_approve_votes(song) || ({});

        if (member_array(this_player()->query_real_name(), approve) != -1)
        {
            write("You have already registered your praise of "
                + "that song; the other members of the Cycle "
                + "must pass judgement on it now.\n");
            return;
        }

        write("Please enter any comments you might have "
            + "about why the song deserves such lofty status:\n");

        clone_object("/obj/edit")->edit(&done_approving(song));
        return;
    }
}

public int
mcreview_approve(string str)
{
    string *songs;
    string lcstr, index, song;
    int songnum;

    if (!strlen(str))
    {
        notify_fail("Usage: mcreview approve <song>.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->query_ballad_submissions();

    if (!songs || !sizeof(songs))
    {
        write("There are no songs submitted for approval.\n");
        return 1;
    }

    if (sscanf(str, "%d", songnum))
    {
        if ((songnum > 0) && (sizeof(songs) >= songnum))
        {
            song = songs[songnum - 1];
        }
    }

    if (!song)
    {
        lcstr = implode(map(explode(str, ""), lower_case), "");
        index = SONG_INDEX;
        songs = filter(songs, &operator(==)(lcstr) @ &index->query_lc_title());

        if (!sizeof(songs))
        {
            write("There is no song titled \"" + str +
                  "\" submitted for approval.\n");
            return 1;
        }

        if (sizeof(songs) > 1)
        {
            write("There are multiple songs titled \"" + str +
                  "\".  Try specifying the song number.\n");
            return 1;
        }

        song = songs[0];
    }

    write("You are approving \"" + SONG_INDEX->query_title(song) + "\" by " +
          SONG_INDEX->query_author(song) + ". Is this correct? (Yes/No)\n");

    clone_object(MINSTREL_OBJ + "yes_no")->get_answer(this_player(),
                                                      &reply_approve(song),
                                                      20.0);
    return 1;
}

public void
done_denying(string song, string text)
{
    string *deny;
    string name;

    setuid();
    seteuid(getuid());

    // It's unlikely, but possible, that the song has been accepted while
    // we were editing so we should check for that.

    if (member_array(song, SONG_INDEX->query_ballad_submissions()) == -1)
    {
        write("The song is no longer available for approval. Perhaps it has " +
              "been accepted already.\n");
        return;
    }

    name = this_player()->query_real_name();

    if (strlen(text) && sizeof(regexp(({ text }), "[^ \n]")))
    {
        SONG_INDEX->add_ballad_comments(song, name, text);
    }

    SONG_INDEX->add_ballad_deny_vote(song, name);

    deny = SONG_INDEX->query_ballad_deny_votes(song) || ({});

    write("You mark the song as unacceptable.\n");

    if (sizeof(deny) > 1)
    {
        write("Two members of the Cycle have deemed this "
            + "song unworthy to be a Ballad; so shall it "
            + "be!\n");
        SONG_INDEX->deny_ballad(song);
    }
}

public void
reply_deny(string song, int reply)
{
    if (reply == 0)
    {
        write("Ok.\n");
        return;
    }

    if (reply == -1)
    {
        write("Timeout. Try again if you wish to deny the song.\n");
        return;
    }

    if (reply == 1)
    {
        string *deny;

        setuid();
        seteuid(getuid());

        deny = SONG_INDEX->query_ballad_deny_votes(song) || ({});

        if (member_array(this_player()->query_real_name(), deny) != -1)
        {
            write("You have already registered your disapproval of "
                + "that song; the other members of the Cycle "
                + "must pass judgement on it now.\n");
            return;
        }

        write("Please enter any comments you might have "
            + "about why the song does not deserve Ballad status:\n");
        clone_object("/obj/edit")->edit(&done_denying(song));
        return;
    }
}

public int
mcreview_deny(string str)
{
    string *songs;
    string lcstr, index, song;
    int songnum;

    if (!strlen(str))
    {
        notify_fail("Usage: mcreview deny <song>.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());

    songs = SONG_INDEX->query_ballad_submissions();

    if (!songs || !sizeof(songs))
    {
        write("There are no songs submitted for approval.\n");
        return 1;
    }

    if (sscanf(str, "%d", songnum))
    {
        if ((songnum > 0) && (sizeof(songs) >= songnum))
        {
            song = songs[songnum - 1];
        }
    }

    if (!song)
    {
        lcstr = implode(map(explode(str, ""), lower_case), "");
        index = SONG_INDEX;
        songs = filter(songs, &operator(==)(lcstr) @ &index->query_lc_title());

        if (!sizeof(songs))
        {
            write("There is no song titled \"" + str +
                  "\" submitted for approval.\n");
            return 1;
        }

        if (sizeof(songs) > 1)
        {
            write("There are multiple songs titled \"" + str +
                  "\".  Try specifying the song number.\n");
            return 1;
        }

        song = songs[0];
    }

    write("You are rejecting \"" + SONG_INDEX->query_title(song) + "\" by " +
          SONG_INDEX->query_author(song) + ". Is this correct? (Yes/No)\n");

    clone_object(MINSTREL_OBJ + "yes_no")->get_answer(this_player(),
                                                      &reply_deny(song),
                                                      20.0);
    return 1;
}

public int
mcreview(string str)
{
    string subcmd, arg;

    if (!strlen(str))
    {
        notify_fail("Usage: mcreview list\n" +
                    "       mcreview read\n" +
                    "       mcreview approve\n" +
                    "       mcreview deny\n");
        return 0;
    }

    if (sscanf(str, "%s %s", subcmd, arg) != 2)
    {
        subcmd = str;
    }

    switch (subcmd)
    {
        case "list":
            return mcreview_list(arg);
        case "read":
            return mcreview_read(arg);
        case "approve":
        case "accept":
            return mcreview_approve(arg);
        case "deny":
        case "reject":
            return mcreview_deny(arg);
    }

    notify_fail("Usage: mcreview list\n" +
                "       mcreview read\n" +
                "       mcreview approve\n" +
                "       mcreview deny\n");
    return 0;
}

public void
write_member_list(string list)
{
    int scrwdth = this_player()->query_option(OPT_SCREEN_WIDTH) - 1;
    if (scrwdth < 11)
    {
        scrwdth = 11;
    }

    this_player()->more(sprintf("%-#" + scrwdth + "s", list));
}

int
filter_minstrels(object who)
{
    string coven;

    if (!MEMBER(who))
    {
        return 0;
    }

    if (who == this_player())
    {
        return 1;
    }

    /* Wizards see everyone */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* Wizards are not shown unless they possess a special prop
     * and are visible
     */
    if (who->query_wiz_level() &&
        (!who->query_prop("_wiz_i_shown_on_minstrel_list") ||
        who->query_invis()))
    {
        return 0;
    }

    /* Jr's are not shown */
    if (extract(who->query_real_name(), -2) == "jr")
    {
        return 0;
    }

    return 1;
}

public int
mcmembers(string arg)
{
    string opts, members_str, type;

    if (arg == 0)
    {
        type = "";
    }
    else if (sscanf(arg, "%s %s", type, opts) != 2)
    {
        type = arg;
    }

    if (!strlen(type) || (type == "active"))
    {
        object *active = filter(users(), filter_minstrels);
        write("Members of the August Order of Minstrels currently active " +
              "in the realms:\n\n");
        members_str = implode(sort_array(map(active, &->query_name())), "\n") + "\n";
    }
    else if (type == "all")
    {
        setuid();
        seteuid(getuid());

        if (!strlen(opts) || wildmatch("alpha*", opts))
        {
            members_str = read_file(MINSTREL_LOG + "members_alpha");
        }
        else if (opts == "start")
        {
            members_str = read_file(MINSTREL_LOG + "members_start");
        }
    }
    else

    {
        notify_fail("Usage: mcmembers active\n" +
                    "       mcmembers all [alpha | start]\n");
        return 0;
    }

    if (strlen(members_str))
    {
        write_member_list(members_str);
    }
    else
    {
        write("No members of the requested type.\n");
    }

    return 1;
}
