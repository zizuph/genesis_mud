int
auto_wear(object ob)
{
    if (!ob->command("wear fur"))
        write("You decide you no longer want to wear the fur.\n");
}
