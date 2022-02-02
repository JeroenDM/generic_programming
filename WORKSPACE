load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
  name = "fmt",
  urls = ["https://github.com/fmtlib/fmt/releases/download/8.0.1/fmt-8.0.1.zip"],
  strip_prefix = "fmt-8.0.1",
  build_file = "//third-party:fmt.BUILD.bazel",
  sha256 = "a627a56eab9554fc1e5dd9a623d0768583b3a383ff70a4312ba68f94c9d415bf",
  workspace_file_content = "",
)

http_archive(
    name = "com_grail_bazel_compdb",
    strip_prefix = "bazel-compilation-database-0.5.2",
    urls = ["https://github.com/grailbio/bazel-compilation-database/archive/0.5.2.tar.gz"],
)

load("@com_grail_bazel_compdb//:deps.bzl", "bazel_compdb_deps")
bazel_compdb_deps()
