//
// Created by nbdy on 25.12.20.
//

#ifndef GPS_DRAWABLE_H
#define GPS_DRAWABLE_H

#include <raylib.h>

class Drawable {
protected:
    Vector2 topLeft;
    Vector2 bottomRight;
    Vector2 center;
    Vector2 size;

public:
    Drawable();
    Drawable(Vector2 center, Vector2 size);

    virtual void draw();
    virtual void work();

    [[nodiscard]] bool mouseOver() const;
    void calculate();

    static Vector2 calculateSize(Vector2 topLeft, Vector2 bottomRight);
    static Vector2 calculateCenterFromTLS(Vector2 topLeft, Vector2 size);
    static Vector2 calculateCenterFromBRS(Vector2 bottomRight, Vector2 size);
    static Vector2 calculateSizeFromTLBR(Vector2 topLeft, Vector2 bottomRight);
    static Vector2 calculateCenterFromTLBR(Vector2 topLeft, Vector2 bottomRight);

    static Vector2 calculateTopLeft(Vector2 center, Vector2 size);
    static Vector2 calculateBottomRight(Vector2 center, Vector2 size);

    [[nodiscard]] Vector2 getTopLeft() const;
    [[nodiscard]] Vector2 getBottomRight() const;
    [[nodiscard]] Vector2 getCenter() const;
    [[nodiscard]] Vector2 getSize() const;

    void setTopLeft(Vector2 value);
    void setBottomRight(Vector2 value);
    void setCenter(Vector2 value);
    void setSize(Vector2 value);

    void resize(Vector2 _center, Vector2 _size);
};


#endif //GPS_DRAWABLE_H
