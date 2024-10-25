# M5 Dial ESPHome with LVGL graphics

This is my PoC on how to use the M5 Dial in combination with Home Assistant entities. I want to use the M5 Dial as a remote for Home Assistant and this implementation shows the possibilities with, i think, some decent feedback from the interface. Its not perfect, but its a nice start for anyone looking for stuff like this.

Take a look at the video of this PoC
https://youtu.be/dOgFMksxVvw

## Features

### Multi use rotary encoder

This PoC allows you to use the rotary encoder in different ways depending on the state it is in. The main goal is to create scrollable pages, and when a pages is entered (through clicking the M5 dial button), the scroll wheel can be used on a widget on that screen. This is done on the first page with the volume control of a media player. On the second page the thermostat can be set higher and lower, and on the third page a slider for the brightness can be altered after the pages is selected. To leave a page, a double click of the button needs to be used.

There is a template button sensor that is used as `enter_button` on the lvgl widget. This way that template button can be clicked when needed. Nothing is implemented, except that the button is not pushed when the rotary encoder is in page scroll mode. When it is in page specific widget scroll mode, it could be used as an enter button.

### Visual feedback

There are breadcrumbs to show on which page you are. This done with 3 arcs that are highlited based on the page that is visible. When the button is in widget scroll mode, an arc the size of all three breadcrumbs is layered over. And last but not least, when the screen goes idle, an arc in the color of the background is layed over. For now every action first unpauses the screen and immediately executes the action, these could be seperate actions.

![idle](/images/thermostat_idle.png) ![idle](/images/thermostat_pageindicator.png) ![idle](/images/thermostat_rotateonpage.png)

The thermostat scroller and the thermostat label will go into blinking mode to show that it is waiting until Home Assistant reports the change back. The new state of the scroller and the target temperature are stored locally and displayed in the widgets, a script waits until the Home Assistant Component of the related entity reports the new setting back.

### Input select support

The select [example](https://esphome.io/components/select/lvgl.html) with a roller (or even a dropdown) will throw my M5 dial into a reboot, bacause of that I have created a function that converts the string of items of a lvgl roller into an array. This way a selected index can be converted into the corresponding text value and that can be sent to Home Assistant. This can also be done vica versa, when an update comes from Home Assistant, the correct index can be set at the roller widget.

### Idle activity

When the screen is in an idle state, the screen does not update when there is a new value from Home Assistant. A few components have the `resume_lvgl` so the screen will be updated. This is regardless of the active screen.

### Scripts

A script is used to alter an Home Assistant entry, this way a delay can be used and therefor not every action is sent to HA immediately. It also allows for canceling an action if needed.

### lv_color_hex

`lv_color_hex` does not work with color substitutes because they are `ESPHOME::Color` and not `lv_color_t`. This means defining the hex twice, but not with `esphomeColorToHex`. This converts the `ESPHOME::Color` to a hexadicmal value which can be used by `lv_color_hex`.