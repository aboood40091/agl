def reencode(path):
    with open(path, encoding="utf-8") as inf:
        text = inf.read()

    with open(path, 'w', encoding="shift-jis") as outf:
        outf.write(text)


reencode('src/detail/aglFileIOMgr.cpp')
reencode('src/postfx/aglDepthOfField.cpp')
