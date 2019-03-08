import pyglet
from pyglet.window import key, mouse

window = pyglet.window.Window()
image = pyglet.resource.image('image/1.jpg')
# music = pyglet.resource.media('')

@window.event
def on_key_press(symbol, modifiers):
    if symbol == key.A:
        window.clear()
        image.blit(0,0)
    if symbol == key.B:
        window.clear()
    print(symbol)

#@window.event
#def on_draw():
#    window.clear()
#    image.blit(0,0)

@window.event
def on_mouse_press(x, y, button, modifiers):
    if button == mouse.LEFT:
        print('Left')
    print(button)
# pyglet.app.run()

platform = pyglet.window.get_platform()
display = platform.get_default_display()
screen = display.get_default_screen()
print(display, platform, screen)
#for config in screen.get_matching_configs(pyglet.gl.Config()):
#    if config.aux_buffers or config.accum_red_size:
#        print(config)
