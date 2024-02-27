# build from source code: You would need the latest GNU make version, for example mac user can install with `brew install make` and export the proper path in zshrc file
gmake -j8 && sudo gmake install PREFIX=/usr/local

# download model if haven't
if [ ! -f "nomic-embed-text-v1.5.Q4_K_M.gguf" ]; then
    wget "https://huggingface.co/nomic-ai/nomic-embed-text-v1.5-GGUF/resolve/main/nomic-embed-text-v1.5.Q4_K_M.gguf"
fi
# copy the base llamafile
cp /usr/local/bin/llamafile rubra.embedding.llamafile
cp .args_embedding .args
# package everything up
zipalign -j0 \
  rubra.embedding.llamafile \
  nomic-embed-text-v1.5.Q4_K_M.gguf \
  .args

rm .args
## run it
# ./rubra.llamafile
