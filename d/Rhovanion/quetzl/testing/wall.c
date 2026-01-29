public int wall_height,
           wall_depth,
           wall_is_stable,
           wall_integrity;

public mapping resist_damage,
               damage_functions;

public string descript_in_room,
              material_type,
              long,
              short,
              *adjlist,
              *link_walls;

public nomask void
create_object()
{
    set_name("wall");
    set_no_show_composite(1);
}

public void
create_wall()
{
}

