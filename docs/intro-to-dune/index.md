# Introduction to Dune

Depending on how you've been following along, you may have several components in
your project. Since these components don't have much in common with each other,
it makes sense to split them up into separate, independent apps. To do that,
we'll have to dive into [Dune](https://dune.build/), an build system designed
for OCaml projects.

## `dune-project` file

The `dune-project` specifies metadata for a project, and should appear at the
root directory of your project. If you've been using the starter
project, then you've been using Dune this whole time and therefore already have
a `dune-project` file:

```
(lang dune 3.8)

;; Use version 0.1 of the melange plugin for dune

(using melange 0.1)

;; Set the name which is used by error messages

(name melange-for-react-devs)
```

The line

```
(using melange 0.1)
```

is necessary because we have to manually enable the Melange plugin for Dune in
order to use it. Note that the version of the Melange Dune plugin is independent
of the version of Melange we're using.

Technically, `dune-project` accepts many more fields, but it’s best to keep it
minimal. Other than `name``, it makes more sense to put the rest of your
project's metadata fields in your `.opam` file, which we'll cover
[later](/todo/).

`dune-project` files use
[S-expressions](https://en.wikipedia.org/wiki/S-expression), which might make
you think of the [Lisp programming
language](https://en.wikipedia.org/wiki/Lisp_(programming_language)). However,
S-expressions are just a convenient syntax for encoding structured data, and
Dune doesn't have the power of a full scripting language.

Each S-expression at the top level is a known as a *stanza*. All the possible
stanzas you can use in `dune-project` can be found in Dune’s [Stanza
Reference](https://dune.readthedocs.io/en/stable/dune-files.html#dune-project).

## `dune` files

Besides `dune-project`, Dune also looks at the `dune` files in our project.
Basically, `dune` files tell Dune about executables, libraries, tests, and
anything else of interest. For example, here's the `dune` file inside the
root directory of your project:

```
;; `dirs` is a stanza to tell dune which subfolders from the current folder
;; (where the `dune` file is) it should process. Here it is saying to include
;; all directories that don't start with . or _, but exclude node_modules.

(dirs :standard \ node_modules)
```

Like `dune-project`, a `dune` consists of one or more *stanzas*. The only stanza
here is [dirs](https://dune.readthedocs.io/en/stable/dune-files.html#dirs),
which tells Dune which directories to include in the build. Note that the
stanzas accepted in `dune` files are not the same as the ones accepted by
`dune-project`. See all `dune` stanzas in Dune's [Stanza
Reference](https://dune.readthedocs.io/en/stable/dune-files.html#dune).

## The `melange.emit` stanza

Let's now take a look at the other `src/dune` file in your project:

```
; `melange.emit` is a Dune stanza that will produce build rules to generate
; JavaScript files from sources using the Melange compiler
; https://dune.readthedocs.io/en/stable/melange.html#melange-emit

(melange.emit
 ; The `target` field is used by Dune to put all JavaScript artifacts in a
 ; specific folder inside `_build/default`
 (target output)
 ; Here's the list of dependencies of the stanza. In this case (being
 ; `melange.emit`), Dune will look into those dependencies and generate rules
 ; with JavaScript targets for the modules in those libraries as well.
 ; Caveat: the libraries need to be specified with `(modes melange)`.
 (libraries reason-react)
 ; The `preprocess` field lists preprocessors which transform code before it is
 ; compiled. These enable, for example, the use of JSX in .re files.
 (preprocess
  (pps melange.ppx reason-react-ppx))
 ; module_systems lets you specify commonjs (the default) or es6
 (module_systems es6))
```

The main stanza of interest for us is
[melange.emit](https://dune.readthedocs.io/en/stable/melange.html#melange-emit),
which tells Dune to turn our OCaml files into JavaScript files and the fields we
use here (`target`, `libraries`, `preprocess`, and `module_systems`) are ones
that we need to use for pretty much every Melange project.
