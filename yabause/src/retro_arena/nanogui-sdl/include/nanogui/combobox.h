/*
    nanogui/combobox.h -- simple combo box widget based on a popup button

    NanoGUI was developed by Wenzel Jakob <wenzel@inf.ethz.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/

#pragma once

#include <nanogui/popupbutton.h>

NAMESPACE_BEGIN(nanogui)

class NANOGUI_EXPORT ComboBox : public PopupButton
{
public:
    /// Create an empty combo box
  ComboBox(Widget *parent);

    /// Create a new combo box with the given items
    //ComboBox(Widget *parent, const std::vector<std::string>& items={});
    ComboBox(Widget *parent, const std::vector<std::string>& items);

    /**
     * \brief Create a new combo box with the given items, providing both short and
     * long descriptive labels for each item
     */
    ComboBox(Widget *parent, const std::vector<std::string> &items,
             const std::vector<std::string> &itemsShort);

    std::function<void(int32_t)> callbackSelect() const { return mCallbackSelect; }
    void setCallbackSelect(const std::function<void(int32_t)> &callback);

    int selectedIndex() const { return mSelectedIndex; }
    void setSelectedIndex(int idx);

    void setItems(const std::vector<std::string> &items, const std::vector<std::string> &itemsShort);
    void setItems(const std::vector<std::string> &items) { setItems(items, items); }
    const std::vector<std::string> &items() const { return mItems; }
    const std::vector<std::string> &itemsShort() const { return mItemsShort; }

    ComboBox& withItems(const std::vector<std::string>& items) {setItems(items); return *this;}

    bool scrollEvent(const Vector2i &p, const Vector2f &rel);

    virtual void save(Serializer &s) const;
    virtual bool load(Serializer &s);
protected:
    std::vector<std::string> mItems, mItemsShort;
    std::function<void(int32_t)> mCallbackSelect;
    int mSelectedIndex;
};

NAMESPACE_END(nanogui)
