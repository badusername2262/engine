#pragma once

struct AABB {
    float minX, maxX, minY, maxY;
};

enum CollisionSide {
    None,
    Top,
    Bottom,
    Left,
    Right
};

CollisionSide checkAABBCollision(AABB a, AABB b) {
    float overlapX = std::min(a.maxX, b.maxX) - std::max(a.minX, b.minX);
    float overlapY = std::min(a.maxY, b.maxY) - std::max(a.minY, b.minY);

    if (overlapX < 0 || overlapY < 0) {
        return None;
    }

    if (overlapX > overlapY) {
        if (a.minY < b.minY) {
            return Top;
        } else {
            return Bottom;
        }
    } else {
        if (a.minX < b.minX) {
            return Left;
        } else {
            return Right;
        }
    }
}
