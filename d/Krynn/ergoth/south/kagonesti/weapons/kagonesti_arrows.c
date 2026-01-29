inherit "/std/arrow";

void create_arrow()
{
    string adj = one_of_list(({"feather-fletched", "stone-pointed",
        "crested"}));
    set_adj(adj);
    set_projectile_id("_kagonesti_arrow_");
    set_hit(35);
    set_pen(35);
}

string get_projectile_long(string str, object for_obj, int num)
{
    return "Although rustic in appearance, "
        + ((num == 1) ? "this arrow" : "these arrows")
        + " look as though they will serve "
        + ((num == 1) ? "its" : "their") + "purpose well. The wooden "
        + ((num == 1) ? "shaft has" : "shafts have")
        + " been affixed with three brown feather vanes to form the fletching."
        + " On the opposite " + ((num == 1) ? "end lies" : "ends lay")
        + " the sharp obsidian "
        + ((num == 1) ? "arrowhead. Both" : "arrowheads. All")
        + " ends have been tightly bound with sinew to increase durability. "
        + "The "  + ((num == 1) ? "shaft has" : "shafts have")
        + "been crested with a pattern of "
        + (random(2) ? "blue" : "green") + ", "
        + (random(2) ? "red" : "yellow") + ", and "
        + (random(2) ? "gold" : "silver") + ".\n";
}
