from distutils.core import setup, Extension

def main():
    setup(name="my",
          version="1.0.0",
          description="My lib de Python",
          author="Eu",
          author_email="your_email@gmail.com",
          ext_modules=[Extension("my", ["my.cpp"])])

if __name__ == "__main__":
    main()