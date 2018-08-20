//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//                2018 Ingo Ruhnke <grumbel@gmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_SUPERTUX_SUPERTUX_COLLISION_SYSTEM_HPP
#define HEADER_SUPERTUX_SUPERTUX_COLLISION_SYSTEM_HPP

#include <vector>
#include <stdint.h>

#include "supertux/collision.hpp"

class DrawingContext;
class MovingObject;
class Rectf;
class Sector;
class Vector;

class CollisionSystem
{
public:
  CollisionSystem(Sector& sector);

  void add(MovingObject* object);
  void remove(MovingObject* object);

  void draw(DrawingContext& context);

  uint32_t collision_tile_attributes(const Rectf& dest, const Vector& mov) const;
  void collision_tilemap(collision::Constraints* constraints,
                         const Vector& movement, const Rectf& dest,
                         MovingObject& object) const;
  void collision_object(MovingObject* object1, MovingObject* object2) const;
  void collision_static(collision::Constraints* constraints,
                        const Vector& movement, const Rectf& dest,
                        MovingObject& object);
  void collision_static_constrains(MovingObject& object);
  void handle_collisions();
  bool is_free_of_tiles(const Rectf& rect, const bool ignoreUnisolid = false) const;
  bool is_free_of_statics(const Rectf& rect, const MovingObject* ignore_object, const bool ignoreUnisolid) const;
  bool is_free_of_movingstatics(const Rectf& rect, const MovingObject* ignore_object) const;
  bool free_line_of_sight(const Vector& line_start, const Vector& line_end, const MovingObject* ignore_object) const;
  std::vector<MovingObject*> get_nearby_objects (const Vector& center, float max_distance) const;

  const std::vector<MovingObject*>& get_moving_objects() const { return m_moving_objects; }

private:
  Sector& m_sector;
  std::vector<MovingObject*>  m_moving_objects;

private:
  CollisionSystem(const CollisionSystem&) = delete;
  CollisionSystem& operator=(const CollisionSystem&) = delete;
};

#endif

/* EOF */
