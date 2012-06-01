#ifndef CONTROL_H_
#define CONTROL_H_

#include "Ref.h"
#include "Rectangle.h"
#include "Vector2.h"
#include "SpriteBatch.h"
#include "Theme.h"
#include "ThemeStyle.h"
#include "Touch.h"
#include "Keyboard.h"

namespace gameplay
{

/**
 * Base class for UI controls.
 */
class Control : public Ref, public AnimationTarget
{
    friend class Form;
    friend class Container;
    friend class Layout;
    friend class AbsoluteLayout;
    friend class VerticalLayout;
    friend class FlowLayout;

public:

    /**
     * The possible states a control can be in.
     */
    enum State
    {
        /**
         * State of an enabled but inactive control.
         */
        NORMAL = 0x01,

        /**
         * State of a control currently in focus.
         */
        FOCUS = 0x02,

        /**
         * State of a control that is currently being acted on,
         * e.g. through touch or mouse-click events.
         */
        ACTIVE = 0x04,

        /**
         * State of a control that has been disabled.
         */
        DISABLED = 0x08,
    };

    /**
     * Defines the set of alignments for positioning controls and justifying text.
     */
    enum Alignment
    {
        // Specify horizontal alignment, use default vertical alignment (ALIGN_TOP).
        ALIGN_LEFT = 0x01,
        ALIGN_HCENTER = 0x02,
        ALIGN_RIGHT = 0x04,
    
        // Specify vertical alignment, use default horizontal alignment (ALIGN_LEFT).
        ALIGN_TOP = 0x10,
        ALIGN_VCENTER = 0x20,
        ALIGN_BOTTOM = 0x40,

        // Specify both vertical and horizontal alignment.
        ALIGN_TOP_LEFT = ALIGN_TOP | ALIGN_LEFT,
        ALIGN_VCENTER_LEFT = ALIGN_VCENTER | ALIGN_LEFT,
        ALIGN_BOTTOM_LEFT = ALIGN_BOTTOM | ALIGN_LEFT,
        ALIGN_TOP_HCENTER = ALIGN_TOP | ALIGN_HCENTER,
        ALIGN_VCENTER_HCENTER = ALIGN_VCENTER | ALIGN_HCENTER,
        ALIGN_BOTTOM_HCENTER = ALIGN_BOTTOM | ALIGN_HCENTER,
        ALIGN_TOP_RIGHT = ALIGN_TOP | ALIGN_RIGHT,
        ALIGN_VCENTER_RIGHT = ALIGN_VCENTER | ALIGN_RIGHT,
        ALIGN_BOTTOM_RIGHT = ALIGN_BOTTOM | ALIGN_RIGHT
    };

    /**
     * A constant used for setting themed attributes on all control states simultaneously.
     */
    static const unsigned char STATE_ALL = NORMAL | FOCUS | ACTIVE | DISABLED;

    /**
     * Implement Control::Listener and call Control::addListener()
     * in order to listen for events on controls.
     */
    class Listener
    {
    public:

        /**
         * Defines the Listener's event types.
         */
        enum EventType
        {
            /**
             * Mouse-down or touch-press event.
             */
            PRESS           = 0x01,

            /**
             * Mouse-up or touch-release event.
             */
            RELEASE         = 0x02,

            /**
             * Event triggered after consecutive PRESS and RELEASE events take place
             * within the bounds of a control.
             */
            CLICK           = 0x04,

            /**
             * Event triggered when the value of a slider, check box, or radio button
             * changes.
             */
            VALUE_CHANGED   = 0x08,

            /**
             * Event triggered when the contents of a text box are modified.
             */
            TEXT_CHANGED    = 0x10
        };

        /**
         * Method called by controls when an event is triggered.
         * 
         * @param control The control triggering the event.
         * @param evt The event triggered.
         */
        virtual void controlEvent(Control* control, EventType evt) = 0;
    };

    /**
     * Position animation property. Data = x, y
     */
    static const int ANIMATE_POSITION = 1;

    /**
     * Position x animation property. Data = x
     */
    static const int ANIMATE_POSITION_X = 2;

    /**
     * Position y animation property. Data = y
     */
    static const int ANIMATE_POSITION_Y = 3;

    /**
     * Size animation property.  Data = width, height
     */
    static const int ANIMATE_SIZE = 4;

    /**
     * Size width animation property.  Data = width
     */
    static const int ANIMATE_SIZE_WIDTH = 5;

    /**
     * Size height animation property.  Data = height
     */
    static const int ANIMATE_SIZE_HEIGHT = 6;

    /**
     * Opacity property.  Data = opacity
     */
    static const int ANIMATE_OPACITY = 7;

    /**
     * Get this control's ID string.
     *
     * @return This control's ID.
     */
    const char* getID() const;

    /**
     * Set the position of this control relative to its parent container.
     *
     * @param x The x coordinate.
     * @param y The y coordinate.
     */
    void setPosition(float x, float y);

    /**
     * Set the desired size of this control, including its border and padding, before clipping.
     *
     * @param width The width.
     * @param height The height.
     */
    virtual void setSize(float width, float height);

    /**
     * Set the bounds of this control, relative to its parent container and including its
     * border and padding, before clipping.
     *
     * @param bounds The new bounds to set.
     */
    virtual void setBounds(const Rectangle& bounds);

    /**
     * Get the bounds of this control, relative to its parent container and including its
     * border and padding, before clipping.
     *
     * @return The bounds of this control.
     */
    const Rectangle& getBounds() const;

    /**
     * Get the x coordinate of this control's bounds.
     *
     * @return The x coordinate of this control's bounds.
     */
    float getX() const;
    
    /**
     * Get the y coordinate of this control's bounds.
     *
     * @return The y coordinate of this control's bounds.
     */
    float getY() const;

    /**
     * Get the width of this control's bounds.
     *
     * @return The width of this control's bounds.
     */
    float getWidth() const;

    /**
     * Get the height of this control's bounds.
     *
     * @return The height of this control's bounds.
     */
    float getHeight() const;

    /**
     * Set the alignment of this control within its parent container.
     *
     * @param alignment This control's alignment.
     */
    void setAlignment(Alignment alignment);

    /**
     * Get the alignment of this control within its parent container.
     *
     * @return The alignment of this control within its parent container.
     */
    Alignment getAlignment() const;

    /**
     * Set this control to fit horizontally within its parent container.
     *
     * @param autoWidth Whether to size this control to fit horizontally within its parent container.
     */
    virtual void setAutoWidth(bool autoWidth);

    /**
     * Get whether this control's width is set to automatically adjust to
     * fit horizontally within its parent container.
     *
     * @return Whether this control's width is set to automatically adjust.
     */
    bool getAutoWidth() const;

    /**
     * Set this control to fit vertically within its parent container.
     *
     * @param autoHeight Whether to size this control to fit vertically within its parent container.
     */
    virtual void setAutoHeight(bool autoHeight);

    /**
     * Get whether this control's height is set to automatically adjust to
     * fit vertically within its parent container.
     *
     * @return Whether this control's height is set to automatically adjust.
     */
    bool getAutoHeight() const;

    /**
     * Set the size of this control's border.
     *
     * @param top The height of the border's top side.
     * @param bottom The height of the border's bottom side.
     * @param left The width of the border's left side.
     * @param right The width of the border's right side.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setBorder(float top, float bottom, float left, float right, unsigned char states = STATE_ALL);

    /**
     * Get the measurements of this control's border for a given state. 
     *
     * @return This control's border.
     */
    const Theme::Border& getBorder(State state = NORMAL) const;

    /**
     * Set the texture region of this control's skin.
     *
     * @param region The texture region, in pixels.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setSkinRegion(const Rectangle& region, unsigned char states = STATE_ALL);

    /**
     * Get the texture region of this control's skin for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return The texture region of this control's skin.
     */
    const Rectangle& getSkinRegion(State state = NORMAL) const;

    /**
     * Get the texture coordinates of an area of this control's skin for a given state.
     *
     * @param area The area of the skin to get the coordinates of.
     * @param state The state to get this property from.
     *
     * @return The texture coordinates of an area of this control's skin.
     */
    const Theme::UVs& getSkinUVs(Theme::Skin::SkinArea area, State state = NORMAL) const;

    /**
     * Set the blend color of this control's skin.
     *
     * @param color The new blend color.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setSkinColor(const Vector4& color, unsigned char states = STATE_ALL);

    /**
     * Get the blend color of this control's skin for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return The blend color of this control's skin.
     */
    const Vector4& getSkinColor(State state = NORMAL) const;

    /**
     * Set this control's margin.
     *
     * @param top Height of top margin.
     * @param bottom Height of bottom margin.
     * @param left Width of left margin.
     * @param right Width of right margin.
     */
    void setMargin(float top, float bottom, float left, float right);

    /**
     * Get this control's margin.
     *
     * @return This control's margin.
     */
    const Theme::Margin& getMargin() const;

    /**
     * Set this control's padding.
     *
     * @param top Height of top padding.
     * @param bottom Height of bottom padding.
     * @param left Width of left padding.
     * @param right Width of right padding.
     */
    void setPadding(float top, float bottom, float left, float right);

    /**
     * Get this control's padding.
     *
     * @return This control's padding.
     */
    const Theme::Padding& getPadding() const;

    /**
     * Set the texture region of an image used by this control.
     *
     * @param id The ID of the image to modify.
     * @param region The new texture region of the image.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setImageRegion(const char* id, const Rectangle& region, unsigned char states = STATE_ALL);

    /**
     * Get the texture region of an image used by this control for a given state.
     *
     * @param id The ID of the image.
     * @param state The state to get this property from.
     *
     * @return The texture region of the specified image.
     */
    const Rectangle& getImageRegion(const char* id, State state) const;

    /**
     * Set the blend color of an image used by this control.
     *
     * @param id The ID of the image to modify.
     * @param color The new blend color of the image.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setImageColor(const char* id, const Vector4& color, unsigned char states = STATE_ALL);

    /**
     * Get the blend color of an image used by this control for a given state.
     *
     * @param id The ID of the image.
     * @param state The state to get this property from.
     *
     * @return The blend color of the specified image.
     */
    const Vector4& getImageColor(const char* id, State state) const;

    /**
     * Get the texture coordinates of an image used by this control for a given state.
     *
     * @param id The ID of the image.
     * @param state The state to get this property from.
     *
     * @return The texture coordinates of the specified image.
     */
    const Theme::UVs& getImageUVs(const char* id, State state) const;

    /**
     * Set the texture region of this control's cursor.
     *
     * @param region The cursor region.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setCursorRegion(const Rectangle& region, unsigned char states);

    /**
     * Get the texture region of this control's cursor for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return The texture region of this control's cursor.
     */
    const Rectangle& getCursorRegion(State state) const;

    /**
     * Set the blend color of this control's cursor.
     *
     * @param color The new blend color.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setCursorColor(const Vector4& color, unsigned char states);

    /**
     * Get the blend color of this control's cursor for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return The blend color of this control's cursor.
     */
    const Vector4& getCursorColor(State state);
    
    /**
     * Get the texture coordinates of this control's cursor for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return The texture coordinates of this control's cursor.
     */
    const Theme::UVs& getCursorUVs(State state);

    /**
     * Set the font used by this control.
     *
     * @param font The new font to use.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setFont(Font* font, unsigned char states = STATE_ALL);

    /**
     * Get the font used by this control for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return the font used by this control.
     */
    Font* getFont(State state = NORMAL) const;

    /**
     * Set this control's font size.
     *
     * @param size The new font size.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setFontSize(unsigned int size, unsigned char states = STATE_ALL);

    /**
     * Get this control's font size for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return This control's font size.
     */
    unsigned int getFontSize(State state = NORMAL) const;

    /**
     * Set this control's text color.
     *
     * @param color The new text color.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setTextColor(const Vector4& color, unsigned char states = STATE_ALL);

    /**
     * Get this control's text color for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return This control's text color.
     */
    const Vector4& getTextColor(State state = NORMAL) const;

    /**
     * Set this control's text alignment.
     *
     * @param alignment The new text alignment.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setTextAlignment(Font::Justify alignment, unsigned char states = STATE_ALL);

    /**
     * Get this control's text alignment for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return This control's text alignment for the given state.
     */
    Font::Justify getTextAlignment(State state = NORMAL) const;

    /**
     * Set whether text is drawn from right to left within this control.
     *
     * @param rightToLeft Whether text is drawn from right to left within this control.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setTextRightToLeft(bool rightToLeft, unsigned char states = STATE_ALL);

    /**
     * Get whether text is drawn from right to left within this control, for a given state.
     *
     * @param state The state to get this property from.
     *
     * @return Whether text is drawn from right to left within this control, for the given state.
     */
    bool getTextRightToLeft(State state = NORMAL) const;

    /**
     * Set the opacity of this control.
     *
     * @param opacity The new opacity.
     * @param states The states to set this property on.
     *               One or more members of the Control::State enum, ORed together.
     */
    void setOpacity(float opacity, unsigned char states = STATE_ALL);

    /**
     * Get the opacity of this control for a given state. 
     *
     * @param state The state to get this property from.
     *
     * @return The opacity of this control for a given state.
     */
    float getOpacity(State state = NORMAL) const;

    /**
     * Get the bounds of this control, relative to its parent container, after clipping.
     *
     * @return The bounds of this control.
     */
    const Rectangle& getClipBounds() const;

    /**
     * Get the content area of this control, in screen coordinates, after clipping.
     *
     * @return The clipping area of this control.
     */
    const Rectangle& getClip() const;

    /**
     * Change this control's state.
     *
     * @param state The state to switch this control to.
     */
    void setState(State state);

    /**
     * Get this control's current state.
     *
     * @return This control's current state.
     */
    State getState() const;

    /**
     * Disable this control.
     */
    void disable();

    /**
     * Enable this control.
     */
    void enable();

    /**
     * Get whether this control is currently enabled.
     *
     * @return Whether this control is currently enabled.
     */
    bool isEnabled();

    /**
     * Set whether this control consumes touch events,
     * preventing them from being passed to the game.
     *
     * @param consume Whether this control consumes touch events.
     */
    void setConsumeTouchEvents(bool consume);

    /**
     * Get whether this control consumes touch events.
     *
     * @return Whether this control consumes touch events.
     */
    bool getConsumeTouchEvents();

    /**
     * Set the style this control will use when rendering.
     *
     * @param style The style this control will use when rendering.
     */
    void setStyle(Theme::Style* style);

    /**
     * Get this control's style.
     *
     * @return This control's style.
     */
    Theme::Style* getStyle() const;

    /**
     * Get this control's z-index.
     *
     * @return This control's z-index.
     */
    int getZIndex() const;

    /**
     * Set this control's z-index.
     *
     * @param zIndex The new z-index.
     */
    void setZIndex(int zIndex);

    /**
     * Add a listener to be notified of specific events affecting
     * this control.  Event types can be OR'ed together.
     * E.g. To listen to touch-press and touch-release events,
     * pass <code>Control::Listener::TOUCH | Control::Listener::RELEASE</code>
     * as the second parameter.
     *
     * @param listener The listener to add.
     * @param eventFlags The events to listen for.
     */
    virtual void addListener(Control::Listener* listener, int eventFlags);

    /**
     * @see AnimationTarget#getAnimationPropertyComponentCount
     */
    virtual unsigned int getAnimationPropertyComponentCount(int propertyId) const;

    /**
     * @see AnimationTarget#getAnimationProperty
     */
    virtual void getAnimationPropertyValue(int propertyId, AnimationValue* value);

    /**
     * @see AnimationTarget#setAnimationProperty
     */
    virtual void setAnimationPropertyValue(int propertyId, AnimationValue* value, float blendWeight = 1.0f);

protected:

    /**
     * Constructor.
     */
    Control();

    /**
     * Destructor.
     */
    virtual ~Control();

    /**
     * Get the overlay type corresponding to this control's current state.
     *
     * @return The overlay type corresponding to this control's current state.
     */
    Theme::Style::OverlayType getOverlayType() const;

    /**
     * Touch callback on touch events.  Controls return true if they consume the touch event.
     *
     * @param evt The touch event that occurred.
     * @param x The x position of the touch in pixels. Left edge is zero.
     * @param y The y position of the touch in pixels. Top edge is zero.
     * @param contactIndex The order of occurrence for multiple touch contacts starting at zero.
     *
     * @return Whether the touch event was consumed by this control.
     *
     * @see Touch::TouchEvent
     */
    virtual bool touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

    /**
     * Keyboard callback on key events.
     *
     * @param evt The key event that occured.
     * @param key If evt is KEY_PRESS or KEY_RELEASE then key is the key code from Keyboard::Key.
     *            If evt is KEY_CHAR then key is the unicode value of the character.
     * 
     * @see Keyboard::KeyEvent
     * @see Keyboard::Key
     */
    virtual void keyEvent(Keyboard::KeyEvent evt, int key);

    /**
     * Called when a control's properties change.  Updates this control's internal rendering
     * properties, such as its text viewport.
     *
     * @param container This control's parent container.
     * @param offset Positioning offset to add to the control's position.
     */
    virtual void update(const Control* container, const Vector2& offset);

    /**
     * Draw the images associated with this control.
     *
     * @param spriteBatch The sprite batch containing this control's icons.
     * @param clip The clipping rectangle of this control's parent container.
     */
    virtual void drawImages(SpriteBatch* spriteBatch, const Rectangle& clip);

    /**
     * Draw this control's text.
     *
     * @param clip The clipping rectangle of this control's parent container.
     */
    virtual void drawText(const Rectangle& clip);

    /**
     * Draws a sprite batch for the specified clipping rect .
     *
     * @param spriteBatch The sprite batch to use.
     * @param clip The clipping rectangle.
     * @param needsClear Whether it needs to be cleared.
     * @param cleared Whether it was previously cleared
     * @param targetHeight The targets height
     */
    virtual void draw(SpriteBatch* spriteBatch, const Rectangle& clip, bool needsClear, bool cleared, float targetHeight);

    /**
     * Initialize properties common to STATE_ALL Controls.
     */
    virtual void initialize(Theme::Style* style, Properties* properties);

    /**
     * Container and classes that extend it should implement this and return true.
     *
     * @return true if this object is of class Container, false otherwise.
     */
    virtual bool isContainer();

    /**
     * Returns whether this control has been modified and requires an update.
     *
     * @return Whether this control has been modified and requires an update.
     */
    virtual bool isDirty();

    /**
     * Get a Control::State enum from a matching string.
     *
     * @param state The string to match.
     *
     * @return The Control::State enum that matches the given string.
     */
    static State getState(const char* state);

    /**
     * Get a Theme::ThemeImage from its ID, for a given state.
     *
     * @param id The ID of the image to retrieve.
     * @param state The state to get this image from.
     *
     * @return The requested Theme::ThemeImage, or NULL if none was found.
     */
    Theme::ThemeImage* getImage(const char* id, State state);

    /**
     * Notify this control's listeners of a specific event.
     *
     * @param eventType The event to trigger.
     */
    void notifyListeners(Listener::EventType eventType);

    /**
     * Gets the Alignment by string.
     *
     * @param alignment The string representation of the Alignment type.
     * @return The Alignment enum value corresponding to the given string.
     */
    static Alignment getAlignment(const char* alignment);

    /** 
     * The Control's ID.
     */ 
    std::string _id;

    /**
     * Determines overlay used during draw().
     */
    State _state;

    /**
     * Position, relative to parent container's clipping window, and desired size.
     */
    Rectangle _bounds;

    /**
     * Position, relative to parent container's clipping window, including border and padding, after clipping.
     */
    Rectangle _clipBounds;

    /**
     * Absolute bounds, including border and padding, before clipping.
     */
    Rectangle _absoluteBounds;

    /**
     * Absolute bounds, including border and padding, after clipping.
     */
    Rectangle _absoluteClipBounds;

    /**
     * Absolute bounds of content area (i.e. without border and padding), before clipping.
     */
    Rectangle _viewportBounds;

    /**
     * Absolute bounds of content area (i.e. without border and padding), after clipping.
     */
    Rectangle _viewportClipBounds;

    /**
     * If the control is dirty and need updating.
     */
    bool _dirty;
    
    /**
     * Flag for whether the Control consume's touch events.
     */
    bool _consumeTouchEvents;
    
    /**
     * The Control's Alignmnet
     */
    Alignment _alignment;
    
    /**
     * Whether the Control's width is auto-sized.
     */
    bool _autoWidth;
    
    /**
     * Whether the Control's height is auto-sized.
     */
    bool _autoHeight;
    
    /**
     * The Control's Theme::Style.
     */
    Theme::Style* _style;
    
    /**
     * Listeners map of EventType's to a list of Listeners.
     */
    std::map<Listener::EventType, std::list<Listener*>*>* _listeners;

    /**
     * The current opacity of the control.
     */
    float _opacity;
    
    /**
     * The z-order of the control.
     */
    int _zIndex;

private:

    /*
     * Constructor.
     */    
    Control(const Control& copy);

    Theme::Style::Overlay** getOverlays(unsigned char overlayTypes, Theme::Style::Overlay** overlays);

    Theme::Style::Overlay* getOverlay(Control::State state) const;

    void overrideStyle();

    void overrideThemedProperties(Properties* properties, unsigned char states);

    void setImageList(Theme::ImageList* imageList, unsigned char states = STATE_ALL);

    void setCursor(Theme::ThemeImage* cursor, unsigned char states = STATE_ALL);

    void setSkin(Theme::Skin* skin, unsigned char states = STATE_ALL);

    Theme::Skin* getSkin(State state);

    void addSpecificListener(Control::Listener* listener, Listener::EventType eventType);
    
    /**
     * Draws the themed border and background of a control.
     *
     * @param spriteBatch The sprite batch containing this control's border images.
     * @param clip The clipping rectangle of this control's parent container.
     */
    virtual void drawBorder(SpriteBatch* spriteBatch, const Rectangle& clip);
    
    bool _styleOverridden;
    Theme::Skin* _skin;
    Rectangle _clearBounds;         // Previous frame's absolute clip bounds, to be cleared if necessary.
};

}

#endif
