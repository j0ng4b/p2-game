/*
The GPLv3 License (GPLv3)

Copyright (c) 2022 Jonatha Gabriel <jonathagabrielns@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include "raylib.h"
#include "world/entity/entity.h"

void entity_update(entity_list_t *entities)
{
    float time = GetTime();
    entity_t *entity;

    for (unsigned i = 0; i < list_size(*entities); i++) {
        entity = list_get(*entities, i);

        if (time - entity->frame.delay >= ENTITY_FRAME_DELAY) {
            entity->frame.current++;

            if (entity->frame.current >= entity->frame.max)
                entity->frame.current = 0;

            entity->frame.delay = GetTime();
        }

        entity->update(entity);
    }
}

void entity_draw(entity_list_t *entities, Rectangle camera)
{
    entity_t *entity;

    for (unsigned i = 0; i < list_size(*entities); i++) {
        entity = list_get(*entities, i);

        if (CheckCollisionPointRec(entity->position, camera))
            entity->draw(entity, camera);
    }
}

void entity_destroy(entity_list_t *entities)
{
    entity_t *entity;

    for (unsigned i = 0; i < list_size(*entities); i++) {
        entity = list_get(*entities, i);
        entity->destroy(entity);
    }

    list_destroy(*entities);

}

