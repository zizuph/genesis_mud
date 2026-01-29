/*
 * A object that is supposed to split up the log in /d/Genesis
 *
 * Made by Nick
 */

#pragma save_binary

inherit "/std/object";

#define READ    1000
#define START   "/d/Genesis/log/"
#define L_START	"/d/Genesis/start/"

void
create_object()
{
    set_name("splitter");
}

void
init()
{
    add_action("split", "split");
}

int
split(string str)
{
    string file;
    int start;

    file = START + str;

    if (!file_size(file) == 1)
    {
        notify_fail("No such log file.\n");
        return 0;
    }

    start = 0;

    if (this_player())
        write("Starting to split " + file + ".\n");

    call_out("split_log", 1, ({ file, start, "", str }) );
    return 1;
}

void
split_log(mixed arr)
{
    string data, *lines, date, rest, *parts;
    int i;

    seteuid(getuid(this_object()));
    data = read_file(arr[0], arr[1], arr[1] + READ);
    if (!data)
    {
        if (this_player())
            write("Done.\n");
        return;
    }

    arr[1] += READ;

    lines = explode(data, "\n");

    for (i = 0; i < sizeof(lines); i++)
    {
        if (!lines[i] || !strlen(lines[i]))
            continue;
        if (sscanf(lines[i], "%sd/Genesis/%s", date, rest) != 2)
        {
            if (strlen(arr[2]))
                write_file(arr[2], lines[i] + "\n");
            else if (this_player())
                    write("Bad line: " + lines[i] + ".\n");
        } else {
            parts = explode(rest, "/");
            if (parts[0] != "start")
                arr[2] = START + "other." + arr[3];
            else if (parts[1] == "hobbit")
                arr[2] = L_START + "hobbit/log/hobbit." + arr[3];
            else if (parts[1] == "dwarf")
                arr[2] = L_START + "dwarf/log/dwarf." + arr[3];
            else if (parts[1] == "elf")
                arr[2] = L_START + "elf/log/elf." + arr[3];
            else if (parts[1] == "gnome")
                arr[2] = L_START + "gnome/log/gnome." + arr[3];
            else if (parts[1] == "human")
                arr[2] = L_START + "human/log/human." + arr[3];
	    else if (parts[1] == "goblin")
		arr[2] = L_START + "goblin/log/goblin." + arr[3];
            else
                arr[2] = START + "strange." + arr[3];

            write_file(arr[2], lines[i] + "\n");
        }
    }
    call_out("split_log", 1, ({ arr[0], arr[1], arr[2], arr[3] }) );
}
