

inherit "/std/room";
#define TP                this_player()
#define TO                this_object()
#define MO_PROP           "_blessed_by_talhurn"
#define NO_OF_LEAVES      3

int leaf;

reset_room()
{
    leaf = NO_OF_LEAVES;
}

create_room()
{
    set_short("Peak");
    set_long(break_string(
        "This is the peak of a great icy mountain.  The air here is " +
        "calm and almost warm.  A large evergreen bush grows here in " +
        "the midst of the ice and snow.\n", 70));

    add_exit("/d/Terel/mountains/summit", "down", 0);
    add_item(({ "evergreen", "leaf", "bush", "Luvico" }),
        "The evergreen looks like a sacred bush.\n");

    add_cmd_item(
        ({ "evergreen", "leaf", "bush", "Luvico" }),
        ({ "smell","pick" }),
	({ "The evergreen smells very good.\n", "@@pick" }));

    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(TO);

    reset_room();
}

pick()
{
    object ob;
    string str;

    if (leaf <= 0) return "You cannot reach it.\n";

    leaf--;

    str = query_item_rest_command();
    if (str == "gently" || TP->query_race_name() == "elf") {
        seteuid(getuid(TO));
        ob = clone_object("/d/Terel/mountains/obj/leaf");
	ob -> add_prop(MO_PROP, 1);
        if (ob->move(TP)) {
            ob->move(TO);
            return "You see a leaf fall to the ground.\n";
        }
        return "You take a leaf from the evergreen bush.\n";
    }

    return "It seems wrong to approach from the evergreen.\n";
}
