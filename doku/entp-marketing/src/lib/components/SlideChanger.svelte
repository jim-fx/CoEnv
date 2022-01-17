<script lang="ts">
	import { slideIndex, slideAmount, nextSlide, previousSlide } from '$lib/stores';
</script>

<div fixed right-4 bottom-4>
	<button bg-transparent border-none color-white on:click={() => previousSlide()}>
		<div class="i-tabler-arrow-left" />
	</button>

	<span>{$slideIndex + 1}/{$slideAmount}</span>

	<button bg-transparent border-none color-white on:click={() => nextSlide()}>
		<div class="i-tabler-arrow-right" />
	</button>
</div>
