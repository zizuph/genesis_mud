string *
query_grid_directions(object from, object to)
{
    int *fromCoords = from->query_coordinates();
    int *toCoords = to->query_coordinates();
    string *directions = ({});

    if (!sizeof(fromCoords) || !sizeof(toCoords))
        return directions;

    if (fromCoords[1] < toCoords[1])
        directions += ({"north"});
    else if (fromCoords[1] > toCoords[1])
        directions += ({"south"});

    if (fromCoords[0] < toCoords[0])
        directions += ({"east"});
    else if (fromCoords[0] > toCoords[0])
        directions += ({"west"});

    if (sizeof(directions) > 1)
        directions += ({implode(directions, "")});

    if (fromCoords[2] < toCoords[2])
        directions += ({"up"});
    else if (fromCoords[2] > toCoords[2])
        directions += ({"down"});

    return directions;
}

string
query_grid_direction(object from, object to)
{
    string *dirs = query_grid_directions(from, to);
    if (sizeof(dirs))
        return dirs[sizeof(dirs) - 1];
    return 0;
}

int
step_towards(object target)
{
    int i, result;
    string *directions = query_grid_directions(environment(this_object()),
            environment(target));

    for (i = sizeof(directions) - 1; i >= 0; i--)
    {
        result = command("$" + directions[i]);
        if (result)
            break;
    }
    if (i < 0)
        return 0;
    return 1;
}

